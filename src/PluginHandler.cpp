#include "PluginHandler.h"

PluginHandler::PluginHandler()
{
    //#if DEBUG == 1
    //cout << "PluginHandler - constructor called. this: 0x" << hex << this << endl;
    //#endif
    m_nPlugins = 0;
    m_nCurrPlugin = -1;

    Scan();
}

PluginHandler::~PluginHandler()
{
    //#if DEBUG == 1
    //cout << "PluginHandler - destructor called. this: 0x" << hex << this << endl;
    //#endif
    for(int i = 0; i < m_nPlugins; i++)
        FreeLibrary(m_hPlugins[i]);
}

/*
 * This function scans for supported plugins in the program directory
 */
void PluginHandler::Scan()
{
    char p[MAX_PATH] = {0};
    GetModuleFileName(GetModuleHandle(0),p,MAX_PATH);

    string path = p;
    path.erase(path.rfind('\\') + 1);

    string search = path;
    search.append("*.dll");

    WIN32_FIND_DATA wfd;
    HANDLE file = FindFirstFile(search.c_str(),&wfd);

    //pmp_PluginInfo mp_PluginInfo;
    //struct mp_plugin_info pi;
    pObtainPluginInterface ObtainPluginInterface;

    do
    {
        HMODULE lib = LoadLibrary(wfd.cFileName);
        //if((mp_PluginInfo = reinterpret_cast<pmp_PluginInfo>(GetProcAddress(lib,"mp_PluginInfo"))))
        if((ObtainPluginInterface = reinterpret_cast<pObtainPluginInterface>(GetProcAddress(lib,"ObtainPluginInterface"))))
        {
            //mp_PluginInfo(&pi);
            IPlugin *pIPlugin;
            ObtainPluginInterface(pIPlugin);
            switch(pIPlugin->GetType())
            {
                case MP_PLUGIN_TYPE_AUDIO:
                    m_audio_plugins[m_nPlugins].m_handle = lib;
                    m_audio_plugins[m_nPlugins].m_pIPlugin = pIPlugin;
                    m_audio_plugins[m_nPlugins].m_name = pIPlugin->GetName();
                    pIPlugin->GetID(&m_audio_plugins[m_nPlugins].m_uuid);

            }
            //#if DEBUG == 1
//            cout << pi.name << " version "
//                << hex << ((pi.version>>24)&0xFF) << "."
//                << ((pi.version>>16)&0xFF) << "."
//                << ((pi.version>>8)&0xFF) << "."
//                << (pi.version&0xFF) << " found!" << endl;
            //#endif
            bool loaded = false;
            for(int i = 0; i < m_nPlugins; i++)
            {
                //if(!m_piPlugins[i].name.compare(pi.name) && m_piPlugins[i].version == pi.version)
                if()
                {
                    //#if DEBUG == 1
                    cout << wfd.cFileName << " already loaded" << endl;
                    //#endif
                    loaded = true;
                }
            }
            if(!loaded)
            {
                m_sPlugins[m_nPlugins] = wfd.cFileName;
                m_hPlugins[m_nPlugins] = lib;
                m_piPlugins[m_nPlugins].name = pi.name;
                m_piPlugins[m_nPlugins++].version = pi.version;
            }
        }
        else
        {
            FreeLibrary(lib);
        }
    }
    while(FindNextFile(file,&wfd));

    cout << endl << m_nPlugins << " plugins loaded:" << endl << endl;

    for(int i = 0; i < m_nPlugins; i++)
    {
        cout << "Pluigin name:\t" << m_piPlugins[i].name << endl;
        cout << "Version:\t" << hex << ((m_piPlugins[i].version>>24)&0xFF) << "."
                << ((m_piPlugins[i].version>>16)&0xFF) << "."
                << ((m_piPlugins[i].version>>8)&0xFF) << "."
                << (m_piPlugins[i].version&0xFF) << endl;
        cout << "File name:\t" << m_sPlugins[i] << endl << endl;
    }

    FindClose(file);
}

HSTREAM PluginHandler::Load(string const& filename)
{
    struct mp_song_info songinf;
    for(int i = 0; i < m_nPlugins; i++)
    {
        pmp_Detect mp_Detect = reinterpret_cast<pmp_Detect>(GetProcAddress(m_hPlugins[i],"mp_Detect"));
        if(mp_Detect((char*)filename.c_str(),&songinf))
        {
            m_nCurrPlugin = i;
            if(songinf.name)
                m_title = songinf.name;
            if(songinf.format)
                m_format = songinf.format;
            if(songinf.info)
                m_comment = songinf.info;
            pmp_InitPlugin mp_InitPlugin = reinterpret_cast<pmp_InitPlugin>(GetProcAddress(m_hPlugins[i],"mp_InitPlugin"));
            mp_InitPlugin((char*)filename.c_str(),44100,16,2);
            return BASS_StreamCreate(44100,2,0,&_streamproc,m_hPlugins[i]);
        }
    }
    return 0;
}

DWORD PluginHandler::GetLengthMS()
{

}

DWORD PluginHandler::NextSubsong()
{
    pmp_NextSubsong mp_NextSubsong = reinterpret_cast<pmp_NextSubsong>(GetProcAddress(m_hPlugins[m_nCurrPlugin],"mp_NextSubsong"));
    return mp_NextSubsong();
}

DWORD PluginHandler::PrevSubsong()
{
    pmp_PreviousSubsong mp_PreviousSubsong = reinterpret_cast<pmp_PreviousSubsong>(GetProcAddress(m_hPlugins[m_nCurrPlugin],"mp_PreviousSubsong"));
    return mp_PreviousSubsong();
}

DWORD CALLBACK PluginHandler::_streamproc(HSTREAM stream, void *data, DWORD len, void *user)
{
    pmp_FillBuffer mp_FillBuffer = reinterpret_cast<pmp_FillBuffer>(GetProcAddress(reinterpret_cast<HMODULE>(user),"mp_FillBuffer"));
    DWORD ret = mp_FillBuffer(data,len);

    //cout << "mp_streamproc - requested " << len << " bytes, recieved " << ret << " bytes." << endl;

    return ret;
}

