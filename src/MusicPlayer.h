#ifndef _MusicPlayer_h_
#define _MusicPlayer_h_

#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

#include "ID3Parser.h"
#include "VorbisCommentParser.h"
#include "PluginHandler.h"

#include "bass.h"

class MusicPlayer
{
    private:
        HMUSIC m_hMusic;
        HSTREAM m_hStream;
        bool m_fMPPlugin;

        string m_path;
        string m_filename;

        MusicInfo m_musicinfo;

        string m_format;
        string m_format_short;
        string m_plugin;

        PluginHandler m_ph;

        int m_nSubsong;

        void _GetID3();
        void _ParseID3v2String(char *buf, int pos, int size, string& out);
    public:
        MusicPlayer(DWORD freq);
        ~MusicPlayer();

        bool Load(string const& filename); // Load a new tune into the music player

        bool Play();
        bool IsPlaying();

        bool Pause();
        bool IsPaused();

        bool Stop();
        bool IsStopped();

        bool SetLoop(bool on);          // Turn loop mode on/off
        bool IsLooped();

        DWORD GetLength();              // Get the length in whatever unit the current format is using
        DWORD GetPos();                 // Get the current position in whatever unit the current format is using
        bool SetPos(DWORD pos);         // Set a new position in whatever unit the current format is using

        DWORD GetLengthMS();            // Get the length in millisecons
        DWORD GetPosMS();               // Get the current position in millisecons

        void NextSubsong();             // Skip to next subsong (if supported)
        void PrevSubsong();             // Skip to previous subsong (if supported)
        int GetCurrentSubsong();        // Get the current subsong number (will return -1 if not supported)

        string const& GetFileName();    // Get the full path of the tune currently playing

        string const& GetArtistName();
        string const& GetSongName();
        string const& GetAlbumName();
        string const& GetYear();
        string const& GetGenre();
        string const& GetComment();

        string const& GetFormat();      // Get the current format currently loaded
        string const& GetFormatShort(); // Get an abbreviated version of the format currently loaded
        string const& GetPluginName();  // Get the name of the plugin currently used
};

#endif //_MusicPlayer_h_
