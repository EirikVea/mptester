#ifndef _PluginHandler_h_
#define _PluginHandler_h_

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <windows.h>
#include "bass.h"

#include "Plugin.h"
#include "MusicInfo.h"

using namespace std;

struct mp_plugin_info
{
    char name[100];
    DWORD version;
};

struct mp_song_info
{
    char *format;
    char *name;
    char *artist;
    int duration;
    int subsongs;
    int voices;
    int steps;
    char *info;
};

class _PluginInfo
{
    public:
        string name;
        DWORD version;
};

class AudioPlugin
{
    public:
        HMODULE m_handle;
        UUID m_uuid;
        string m_name;
        DWORD m_version;
        IPlugin *m_pIPlugin;
        IAudioPlugin *m_pIAudioPlugin;
        IMusicInfo *m_pIMusicInfo;
        IModuleInfo *m_pIModuleInfo;
};

class PluginHandler : public IAudioPlugin, IVisualPlugin, IMusicInfo, IModuleInfo
{
    private:
        AudioPlugin m_audio_plugins[1024];
        //HMODULE m_hPlugins[1024];
        //string m_sPlugins[1024];
        //_PluginInfo m_piPlugins[1024];
        int m_nPlugins;
        int m_nCurrPlugin;

//        string m_title;   // Song title
//        string m_format;  // Artist name
//        string m_comment; // Comment

//        typedef void (*pmp_PluginInfo)(struct mp_plugin_info*);
//        typedef bool (*pmp_Detect)(char*,struct mp_song_info*);
//        typedef bool (*pmp_InitPlugin)(char*,int,int,int);
//        typedef DWORD (*pmp_FillBuffer)(void*,DWORD);
//
//        typedef DWORD (*pmp_NextSubsong)();
//        typedef DWORD (*pmp_PreviousSubsong)();

        typedef DWORD (*pObtainPluginInterface)(IPlugin*);
        typedef DWORD (*pReleasePluginInterface)(void);

        static DWORD CALLBACK _streamproc(HSTREAM stream, void *data, DWORD len, void *user);
    protected:
        int FillBuffer(void* data, int length); // Fills a buffer of desired length with PCM data
    public:
        PluginHandler();
        ~PluginHandler();

        void Scan(); // Scan for new plugins
//
//        HSTREAM Load(string const& filename); // Loads a module by filename
//
//        DWORD GetLengthMS();
//        DWORD NextSubsong();
//        DWORD PrevSubsong();
//
//        string const& GetTitle() { return m_title; };
//        string const& GetFormat() { return m_format; };
//        string const& GetComment() { return m_comment; };

    /* IPlugin interface begin */
        DWORD GetVersion();     // Get the version of this plugin
        DWORD GetType();        // Get the type of this plugin
        const char* GetName();  // Get the name of this plugin
        // Get the UUID of the plugin. Will also return the UUID as a sting Format: XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
        const char* GetID(UUID& uuid);
    /* IPlugin interface end */

    /* IAudioPlugin interface begin */
        void Initialize(int frequency, int bps, int channels);
        bool Load(char* filename);
        void Unload();

        bool HasValidData();
        DWORD GetSubsongCnt();

        DWORD GetLength(DWORD subsong);
        DWORD GetCurPos(DWORD subsong);
        DWORD SetCurPos(DWORD subsong, DWORD pos);

        void SetLoopMode(bool loopmode);
        bool IsLooped();

        void Play();
        void Pause();
        void Stop();
        DWORD NextSubsong();
        DWORD PrevSubsong();

        DWORD FillBuffer(void* pbuffer, DWORD length); // The plugin host calls this when it wants a new audio frame
    /* IAudioPlugin interface end */

    /* IMusicInfo interface begin */
        const char* Artist();       // Artist
        const char* Title();        // Title
        const char* Album();        // Album
        const char* Year();         // Year/date as a string
        const char* Comments();     // Comments, info, message
        const char* Duration();     // Format hh:mm:ss
        const char* Format();       // Format name
        const char* FormatShort();  // Short format, maximum 4 characters
        const char* FileName();     // Only filename, not complete path
    /* IMusicInfo interface end */
};

#endif // _PluginHandler_h_
