#ifndef _Plugin_h_
#define _Plugin_h_

using namespace std;

#include <string>
#include <iostream>
#include <windows.h>

#define MP_PLUGIN_TYPE_AUDIO    0
#define MP_PLUGIN_TYPE_VISUAL   1

//struct mp_plugin_info
//{
//    string const& name;
//    DWORD version;
//    DWORD type;
//};
//
//struct mp_song_info
//{
//    string const& format;
//    string const& format_short;
//    string const& name;
//    string const& artist;
//    string const& info;
//    DWORD duration; // Song length in milliseconds/number of tracksteps
//    DWORD subsongs; // -1 if none
//    DWORD channels; // number of channels/voices
//};

/* IPlugin interface
 *
 *
 * Every plugin must implement these methods
 */
class IPlugin
{
    public:
        virtual DWORD GetVersion() = 0; // Get the version of this plugin
        virtual DWORD GetType() = 0;    // Get the type of this plugin
        virtual const char* GetName() = 0;    // Get the name of this plugin
        // Get the UUID of the plugin. Will also return the UUID as a sting Format: XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
        virtual const char* GetID(UUID& uuid);
};

/* IAudioPlugin interface
 *
 *
 * Every audio plugin must implement these methods
 */
class IAudioPlugin
{
    public:
        virtual void Initialize(int frequency, int bps, int channels) = 0;
        virtual bool Load(char* filename) = 0;
        virtual void Unload() = 0;

        virtual bool HasValidData() = 0;
        virtual DWORD GetSubsongCnt() = 0;

        virtual DWORD GetLength(DWORD subsong) = 0;
        virtual DWORD GetCurPos(DWORD subsong) = 0;
        virtual DWORD SetCurPos(DWORD subsong, DWORD pos) = 0;

        virtual void SetLoopMode(bool loopmode) = 0;
        virtual bool IsLooped() = 0;

        virtual void Play() = 0;
        virtual void Pause() = 0;
        virtual void Stop() = 0;
        virtual DWORD NextSubsong() = 0;
        virtual DWORD PrevSubsong() = 0;

        virtual DWORD FillBuffer(void* pbuffer, DWORD length) = 0; // The plugin host calls this when it wants a new audio frame
};

/* IVisualPlugin interface
 *
 *
 * Every visual plugin must implement these methods
 */
class IVisualPlugin
{
    private:
    public:
};

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

DWORD DLL_EXPORT ObtainPluginInterface(IPlugin *pIPlugin);
DWORD DLL_EXPORT ReleasePluginInterface();

#ifdef __cplusplus
}
#endif


#endif // _Plugin_h_
