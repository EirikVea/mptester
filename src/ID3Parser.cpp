#include "ID3Parser.h"

ID3Parser::ID3Parser(HSTREAM h, MusicInfo &mi)
{
    ID3_version = 0xFFFFFFFF;

    if(!h)
        return;

    BASS_CHANNELINFO info;
    BASS_ChannelGetInfo(h,&info);

    if(info.ctype != BASS_CTYPE_STREAM_MP1
       && info.ctype != BASS_CTYPE_STREAM_MP2
       && info.ctype != BASS_CTYPE_STREAM_MP3)
       return;

    TAG_ID3 *id3;
    const char *pframes;

    pframes = BASS_ChannelGetTags(h,BASS_TAG_ID3V2);
    if(BASS_ErrorGetCode() == BASS_OK && pframes[0] == 'I' && pframes[1] == 'D' && pframes[2] == '3')
    {
        ID3_version = 0x02000000 | ((DWORD)pframes[3] << 16);

        if((ID3_version & 0x00FF0000) == 0x00040000 || (ID3_version & 0x00FF0000) == 0x00030000)
        {
            // ID3v2.3 or ID3v2.4
            // Artist
            _GetID3v2String(pframes,ID3V2.TPE1,"TPE1");

            // Title
            _GetID3v2String(pframes,ID3V2.TIT2,"TIT2");

            // Album
            _GetID3v2String(pframes,ID3V2.TALB,"TALB");

            // Year
            if((ID3_version & 0x00FF0000) == 0x00030000)
                _GetID3v2String(pframes,ID3V2.TYER,"TYER");
            else
                _GetID3v2String(pframes,ID3V2.TDRC,"TDRC");

            // Genre
            _GetID3v2String(pframes,ID3V2.TCON,"TCON");

            // Comment
            //_GetID3v2String(pframes,ID3V2.COMM,"COMM");
        }
        else
        {
            // ID3v2.1
            // Artist
            _GetID3v2String(pframes,ID3V2.TPE1,"TP1");

            // Title
            _GetID3v2String(pframes,ID3V2.TIT2,"TT2");

            // Album
            _GetID3v2String(pframes,ID3V2.TALB,"TAL");

            // Year
            _GetID3v2String(pframes,ID3V2.TYER,"TYE");

            // Genre
            _GetID3v2String(pframes,ID3V2.TCON,"TCO");

            // Comment
            //_GetID3v2String(pframes,ID3V2.COMM,"COM");
        }
    }
    if(ID3_version == 0xFFFFFFFF)
    {
        id3 = (TAG_ID3*)BASS_ChannelGetTags(h,BASS_TAG_ID3);
        if(BASS_ErrorGetCode() == BASS_OK && id3->id[0] == 'T' && id3->id[1] == 'A' && id3->id[2] == 'G')
        {
            ID3_version = 0x01000000;

            ID3V1.title = id3->title;
            if(ID3V1.title.length() >= 30)
                ID3V1.title.erase(30,string::npos);

            ID3V1.artist = id3->artist;
            if(ID3V1.artist.length() >= 30)
                ID3V1.artist.erase(30,string::npos);

            ID3V1.album = id3->album;
            if(ID3V1.album.length() >= 30)
                ID3V1.album.erase(30,string::npos);

            ID3V1.year = id3->year;
            if(ID3V1.year.length() >= 4)
                ID3V1.year.erase(4,string::npos);

            ID3V1.comment = id3->comment;
            if(ID3V1.comment.length() >= 30)
                ID3V1.comment.erase(30,string::npos);

            if(id3->genre < 126 && id3->genre >= 0)
                ID3V1.genre = ID3_GENRES[id3->genre];
        }
    }

    /*** Fill in music info ***/
    // Title
    if((ID3_version & 0xFF000000) == 0x01000000)
        mi.songname = ID3V1.title;
    // 'Title/Songname/Content description
    else if(ID3V2.TIT2.text.compare(""))
        mi.songname = ID3V2.TIT2.text;

    // Artist
    if((ID3_version & 0xFF000000) == 0x01000000)
        mi.artist = ID3V1.artist;
    // 'Lead artist/Lead performer/Soloist/Performing group'
    else if(ID3V2.TPE1.text.compare(""))
        mi.artist = ID3V2.TPE1.text;

    // Album
    if((ID3_version & 0xFF000000) == 0x01000000)
        mi.album = ID3V1.album;
    // 'Album/Movie/Show title'
    else if(ID3V2.TALB.text.compare(""))
        mi.album = ID3V2.TALB.text;

    // Year
    if((ID3_version & 0xFF000000) == 0x01000000)
        mi.year = ID3V1.year;
    // 'Year' deprecated in ID3v2.4
    else if(ID3V2.TYER.text.compare(""))
        mi.year = ID3V2.TYER.text;
    // And replaced by 'Recording time'
    else if(ID3V2.TDRC.text.compare(""))
        mi.year = ID3V2.TDRC.text;

    // Genre
    if((ID3_version & 0xFF000000) == 0x01000000)
        mi.genre = ID3V1.genre;
    // 'Content type (ID3v1 genre or custom string)'
    else if(ID3V2.TCON.text.compare(""))
        mi.genre = ID3V2.TCON.text;

    // Comment
    if((ID3_version & 0xFF000000) == 0x01000000)
        mi.comment = ID3V1.comment;
    else if(ID3V2.COMM.text.compare(""))
        mi.comment = ID3V2.COMM.text;
}

ID3Parser::~ID3Parser()
{

}

bool ID3Parser::IsValid()
{
    return ID3_version != 0xFFFFFFFF;
}

string const& ID3Parser::GetTitle()
{
    // Check if this is ID3V1 first
    if((ID3_version & 0xFF000000) == 0x01000000)
        return ID3V1.title;

    // 'Title/Songname/Content description
    if(ID3V2.TIT2.text.compare(""))
        return ID3V2.TIT2.text;

    // Try 'Content group description'
    if(ID3V2.TIT1.text.compare(""))
        return ID3V2.TIT1.text;

    // Last resort 'Subtitle/Description refinement'
    return ID3V2.TIT3.text;
}

string const& ID3Parser::GetArtist()
{
    // Check if this is ID3V1 first
    if((ID3_version & 0xFF000000) == 0x01000000)
        return ID3V1.artist;

    // 'Lead artist/Lead performer/Soloist/Performing group'
    if(ID3V2.TPE1.text.compare(""))
        return ID3V2.TPE1.text;

    // Last resort 'Band/Orchestra/Accompaniment'
    return ID3V2.TPE2.text;
}

string const& ID3Parser::GetAlbum()
{
    // Check if this is ID3V1 first
    if((ID3_version & 0xFF000000) == 0x01000000)
        return ID3V1.album;

    // 'Album/Movie/Show title'
    return ID3V2.TALB.text;
}

string const& ID3Parser::GetYear()
{
    // Check if this is ID3V1 first
    if((ID3_version & 0xFF000000) == 0x01000000)
        return ID3V1.year;

    // 'Year' deprecated in ID3v2.4
    if(ID3V2.TYER.text.compare(""))
        return ID3V2.TYER.text;

    // And replaced by 'Recording time'
    return ID3V2.TDRC.text;
}

string const& ID3Parser::GetGenre()
{
    // Check if this is ID3V1 first
    if((ID3_version & 0xFF000000) == 0x01000000)
        return ID3V1.genre;

    return ID3V2.TCON.text;
}

string const& ID3Parser::GetComment()
{
    // Check if this is ID3V1 first
    if((ID3_version & 0xFF000000) == 0x01000000)
        return ID3V1.comment;

    return ID3V2.COMM.text;
}

bool ID3Parser::_GetID3v2String(const char *pframes, ID3V2STR& frame, const char search_key[])
{
    int ver = (ID3_version & 0x00FF0000) >> 16;

    const int ID3V2_HEADER_SIZE = 10;

    int tag_len = (pframes[9] & 0x7F) + ((pframes[8] & 0x7F) << 7) + ((pframes[7] & 0x7F) << 14) + ((pframes[6] & 0x7F) << 21) + 10;
    bool synch = ((pframes[5] & 0x80) != 0) ? true : false;
    bool ext_hdr = ((pframes[5] & 0x40) != 0) ? true : false;
    int ext_hdr_len = 0;

    if(ext_hdr)
    {
        ext_hdr_len = (pframes[12] << 7) | (pframes[11] << 14) | (pframes[10] << 21);
    }

    char *tag_buffer = new char[tag_len];
    memcpy(tag_buffer,pframes + ID3V2_HEADER_SIZE + ext_hdr_len,tag_len);

    int len = tag_len;

    if(synch)
    {
        int tpos = 0;
        char *tbuffer = new char[tag_len];

        for(int i = 0; i < tag_len; i++)
        {
            if(i < tag_len - 1 && (tag_buffer[i] & 0xFF) == 0xFF && tag_buffer[i+1] == 0)
            {
                tbuffer[tpos++] = (char)0xFF;
                i++;
                continue;
            }
            tbuffer[tpos++] = tag_buffer[i];
        }
        len = tpos;
        delete tag_buffer;
        tag_buffer = tbuffer;
    }

    int pos = 0;
    const int ID3V2_FRAME_SIZE = (ver < 3) ? 6 : 10;

    while(true)
    {
        int rem = len - pos;

        if(rem < ID3V2_FRAME_SIZE)
            break;
        if(tag_buffer[pos] < 'A' || tag_buffer[pos] > 'Z')
            break;

        string framename;
        framename.clear();
        int frame_len;

        if(ver < 3)
        {
            framename.append(tag_buffer + pos,0,3);
            frame_len = ((tag_buffer[pos+5] & 0xFF)) + ((tag_buffer[pos+4] & 0xFF) << 8 ) + ((tag_buffer[pos+3] & 0xFF) << 16 );
        }
        else
        {
            framename.append(tag_buffer + pos,0,4);
            frame_len = (tag_buffer[pos+7] & 0xFF) + ((tag_buffer[pos+6] & 0xFF) << 8 ) + ((tag_buffer[pos+5] & 0xFF) << 16 ) + ((tag_buffer[pos+4] & 0xFF) << 24 );
        }

        if(pos + frame_len > len)
            break;

        if(!framename.compare(search_key))
        {
            _ParseID3v2String(tag_buffer,pos + ID3V2_FRAME_SIZE, frame_len, frame);
            return true;
        }

        pos += frame_len + ID3V2_FRAME_SIZE;
    }

    return false;
}

void ID3Parser::_ParseID3v2String(char *pframes, int pos, int size, ID3V2STR& out)
{
    if(size < 2)
        return;

    out.encoding = pframes[pos];
    if(out.encoding != 0 && out.encoding != 3)
    {
        char *buf = new char[size - 2];
        char *nbuf = new char[((size - 2) >> 1) + 1];
        memcpy(buf,pframes + pos + 2, size - 2);

        for(int i = 0, j = 1; i < (size - 2) >> 1; i++,j+=2)
            nbuf[i] = buf[j];

        nbuf[(size - 2) >> 1] = 0;
        out.text.assign(nbuf);

        delete buf;
        delete nbuf;
    }
    else
        out.text.assign(pframes + pos + 1, 0, size - 1);
}
