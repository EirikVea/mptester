#include "MusicPlayer.h"

//MusicPlayer::MusicPlayer()
//{
//    MusicPlayer(44100);
//}

MusicPlayer::MusicPlayer(DWORD freq)
{
    //#if DEBUG == 1
    //cout << "MusicPlayer - constructor called. this: 0x" << hex << this << endl;
    //#endif

    m_hMusic = NULL;
    m_hStream = NULL;
    m_fMPPlugin = false;

    BASS_Init(-1,freq,0,0,NULL);
}

MusicPlayer::~MusicPlayer()
{
    //#if DEBUG == 1
    //cout << "MusicPlayer - destructor called. this: 0x" << hex << this << endl;
    //#endif
}

bool MusicPlayer::Load(string const& filename)
{
    // Free any previously allocated tune
    BASS_MusicFree(m_hMusic);
    m_hMusic = NULL;
    BASS_StreamFree(m_hStream);
    m_hStream = NULL;
    m_fMPPlugin = false;
    // TODO: MusicPlayer::Load - Add call for releasing any plugin loaded data

    m_path.clear();
    m_filename.clear();

    m_musicinfo.artist.clear();
    m_musicinfo.songname.clear();
    m_musicinfo.album.clear();

    m_format.clear();
    m_format_short.clear();
    m_plugin.clear();

    // First check to see if this is a tracker format supported by BASS
    if((m_hMusic = BASS_MusicLoad(false,filename.c_str(),0,0,BASS_MUSIC_RAMP | BASS_MUSIC_LOOP | BASS_MUSIC_PRESCAN,0)))
    {
        //cout << "Module supported by BASS" << endl;
    }
    // Then check if format is supported by any plugin
    // TODO: MusicPlayer::Load - Add call/code for loading tune via plugin
    else if((m_hStream = m_ph.Load(filename)))
    {
        m_fMPPlugin = true;
        //cout << "Module supported by plugin" << endl;
    }

    // Finally try to open as a stream (MP3, MP2, MP1, OGG, WAV, AIFF or BASS plugin supported file)
    else if(0 == (m_hStream = BASS_StreamCreateFile(false,filename.c_str(),0,0,0)))
        return false; // Returns false meaning that this file is not supported by the music player
    //else
        //cout << "Stream supported by BASS" << endl;

    m_path = m_filename = filename;
    m_path.erase(m_path.rfind('\\') + 1);
    m_filename.erase(0,m_filename.rfind('\\') + 1);

    BASS_CHANNELINFO info;

    // Get info about the tune
    // TODO: This must be done in a smarter way
    if(m_hMusic)
    {
        BASS_ChannelGetInfo(m_hMusic,&info);
        m_musicinfo.songname = BASS_ChannelGetTags(m_hMusic,BASS_TAG_MUSIC_NAME);
    }
    else if (m_hStream && m_fMPPlugin)
    {
        m_musicinfo.songname = m_ph.GetTitle();
        m_musicinfo.comment = m_ph.GetComment();
        m_format = m_ph.GetFormat();
    }
    else if(m_hStream)
    {
        BASS_ChannelGetInfo(m_hStream,&info);
        ID3Parser id3(m_hStream,m_musicinfo);
        VorbisCommentParser vcp(m_hStream,m_musicinfo);
    }

    // Fallback to file name if no title is obtained
    string tmp, str;
    str = m_musicinfo.songname;
    for (unsigned int i = 0; i < str.length(); i++)
        if (str[i] != ' ') tmp += str[i];
    str = tmp;
    if(!str.compare(""))
        m_musicinfo.songname = m_filename;

    switch(info.ctype)
    {
        case BASS_CTYPE_STREAM_OGG:
            m_format = "Ogg Vorbis";
            m_format_short = "OGG";
            break;
        case BASS_CTYPE_STREAM_MP1:
            m_format = "MPEG-1 Audio Layer I";
            m_format_short = "MP1";
            break;
        case BASS_CTYPE_STREAM_MP2:
            m_format = "MPEG-1 Audio Layer II";
            m_format_short = "MP2";
            break;
        case BASS_CTYPE_STREAM_MP3:
            m_format = "MPEG-1 Audio Layer III";
            m_format_short = "MP3";
            break;
        case BASS_CTYPE_STREAM_AIFF:
            m_format = "Audio Interchange File Format";
            m_format_short = "AIFF";
            break;
        case BASS_CTYPE_STREAM_CA:
            m_format = "Apple Core Audio Format";
            m_format_short = "CA";
            break;
        case BASS_CTYPE_STREAM_MF:
            m_format = "Media Foundation";
            m_format_short = "MF";
            break;
        case BASS_CTYPE_STREAM_WAV:
        case BASS_CTYPE_STREAM_WAV_FLOAT:
        case BASS_CTYPE_STREAM_WAV_PCM:
            m_format = "Waveform Audio File Format RIFF/WAVE";
            m_format_short = "WAV";
            break;
        case BASS_CTYPE_MUSIC_MOD:
            m_format = "Generic MOD";
            m_format_short = "MOD";
            break;
        case BASS_CTYPE_MUSIC_MTM:
            m_format = "MultiTracker";
            m_format_short = "MTM";
            break;
        case BASS_CTYPE_MUSIC_S3M:
            m_format = "ScreamTracker 3";
            m_format_short = "S3M";
            break;
        case BASS_CTYPE_MUSIC_XM:
            m_format = "FastTracker 2";
            m_format_short = "XM";
            break;
        case BASS_CTYPE_MUSIC_IT:
            m_format = "Impulse Tracker";
            m_format_short = "IT";
            break;
        case BASS_CTYPE_MUSIC_MO3:
            m_format = "MO3 format";
            m_format_short = "MO3";
            break;
    }

    return true;
}

bool MusicPlayer::Play()
{
    if(m_hMusic)
        return BASS_ChannelPlay(m_hMusic,false);
    if(m_hStream)
        return BASS_ChannelPlay(m_hStream,false);

    return false;
}

bool MusicPlayer::IsPlaying()
{
    if(m_hMusic)
        return BASS_ACTIVE_PLAYING & BASS_ChannelIsActive(m_hMusic);
    if(m_hStream)
        return BASS_ACTIVE_PLAYING & BASS_ChannelIsActive(m_hStream);

    return false;
}

// Get the length in millisecons
DWORD MusicPlayer::GetLengthMS()
{
    if(m_hMusic)
        return BASS_ChannelBytes2Seconds(m_hMusic,BASS_ChannelGetLength(m_hMusic,BASS_POS_BYTE)) * 1000;
    if(m_hStream)
        return BASS_ChannelBytes2Seconds(m_hStream,BASS_ChannelGetLength(m_hStream,BASS_POS_BYTE)) * 1000;
    if(m_hStream && m_fMPPlugin)
        return m_ph.GetLengthMS();

    return -1;
}

// Get the current position in millisecons
DWORD MusicPlayer::GetPosMS()
{
    if(m_hMusic)
        return BASS_ChannelBytes2Seconds(m_hMusic,BASS_ChannelGetPosition(m_hMusic,BASS_POS_BYTE)) * 1000;
    if(m_hStream)
        return BASS_ChannelBytes2Seconds(m_hStream,BASS_ChannelGetPosition(m_hStream,BASS_POS_BYTE)) * 1000;

    return -1;
}

// Skip to next subsong (if supported)
void MusicPlayer::NextSubsong()
{
    m_nSubsong = m_ph.NextSubsong();
}

// Skip to previous subsong (if supported)
void MusicPlayer::PrevSubsong()
{
    m_nSubsong = m_ph.PrevSubsong();
}

// Get the current subsong number (will return -1 if not supported)
int MusicPlayer::GetCurrentSubsong()
{
    if(!m_fMPPlugin)
        return -1;

    return m_nSubsong;
}

// Get the full path of the tune currently playing
string const& MusicPlayer::GetFileName()
{
    return m_filename;
}

string const& MusicPlayer::GetArtistName()
{
    return m_musicinfo.artist;
}

string const& MusicPlayer::GetSongName()
{
    return m_musicinfo.songname;
}

string const& MusicPlayer::GetAlbumName()
{
    return m_musicinfo.album;
}

string const& MusicPlayer::GetYear()
{
    return m_musicinfo.year;
}

string const& MusicPlayer::GetGenre()
{
    return m_musicinfo.genre;
}

string const& MusicPlayer::GetComment()
{
    return m_musicinfo.comment;
}

// Get the current format currently loaded
string const& MusicPlayer::GetFormat()
{
    return m_format;
}

// Get an abbreviated version of the format currently loaded
string const& MusicPlayer::GetFormatShort()
{
    return m_format_short;
}

// Get the name of the plugin currently used
string const& MusicPlayer::GetPluginName()
{
    return m_plugin;
}
