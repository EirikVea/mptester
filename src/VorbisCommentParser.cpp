#include "VorbisCommentParser.h"

VorbisCommentParser::VorbisCommentParser(HSTREAM h, MusicInfo &mi)
{
    valid = false;

    if(!h)
        return;

    BASS_CHANNELINFO info;
    BASS_ChannelGetInfo(h,&info);

    valid = (info.ctype == BASS_CTYPE_STREAM_OGG);

    if(!valid)
        return;

    const char *ogg_comments = BASS_ChannelGetTags(h,BASS_TAG_OGG);

    if(!ogg_comments)
        return;

    int len = 0;
    bool end = false;
    while(!end)
    {
        if(ogg_comments[len] == '\0' && ogg_comments[len+1] == '\0')
            end = true;
        len++;
    }

    char *comments = new char[len];
    memcpy(comments,ogg_comments,len);

    if(!_GetField(comments,"ARTIST",artist))
        _GetField(comments,"artist",artist);
    //cout << "ARTIST: " << artist << endl;
    mi.artist = artist;

    if(!_GetField(comments,"TITLE",title))
        _GetField(comments,"title",title);
    //cout << "TITLE: " << title << endl;
    mi.songname = title;

    if(!_GetField(comments,"DATE",year))
       _GetField(comments,"date",year);
    //cout << "DATE: " << year << endl;
    mi.year = year;

    if(!_GetField(comments,"COMMENT",comment))
        _GetField(comments,"comment",comment);
    //cout << "COMMENT: " << comment << endl;
    mi.comment = comment;

    if(!_GetField(comments,"GENRE",genre))
        _GetField(comments,"genre",genre);
    //cout << "GENRE: " << genre << endl;
    mi.genre = genre;

    delete comments;
}

VorbisCommentParser::~VorbisCommentParser()
{

}

bool VorbisCommentParser::IsValid()
{
    return valid;
}

bool VorbisCommentParser::_GetField(char *comments ,const char fieldname[], string& out)
{
    string temp;
    char *t = comments;
    int pos;

    while(t[0] != '\0')
    {
        temp = t;
        pos = temp.find(fieldname);

        if(pos != string::npos)
        {
            temp.erase(0,strlen(fieldname) + 1);
            out = temp;
            return true;
        }
        t += strlen(t) + 1;
    }
    return false;
}
