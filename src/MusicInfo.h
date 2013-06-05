#ifndef _MusicInfo_h_
#define _MusicInfo_h_

using namespace std;

typedef struct _MusicInfo
{
    string artist;
    string songname;
    string album;
    string year;
    string genre;
    string comment;
} MusicInfo;

/* IMusicInfo interface
 *
 *
 * To support basic music informationm, the plugin must implement this interface
 */
class IMusicInfo
{
    public:
        virtual const char* Artist() = 0;       // Artist
        virtual const char* Title() = 0;        // Title
        virtual const char* Album() = 0;        // Album
        virtual const char* Year() = 0;         // Year/date as a string
        virtual const char* Comments() = 0;     // Comments, info, message
        virtual const char* Duration() = 0;     // Format hh:mm:ss
        virtual const char* Format() = 0;       // Format name
        virtual const char* FormatShort() = 0;  // Short format, maximum 4 characters
        virtual const char* FileName() = 0;     // Only filename, not complete path
};

/* IModuleInfo interface
 *
 *
 * To support extended module information, the plugin must implement this interface
 */
class IModuleInfo : public IMusicInfo
{
    public:
        virtual void*/*List**/ GetTracksteps() = 0;                 // Pointer to a List of tracksteps
        virtual void*/*List**/ GetPatterns(int step_number) = 0;    // Pointer to a List of the patterns of the supplied step
        virtual void*/*List**/ GetSamples() = 0;                    // Pointer to a List of all samples
        virtual void*/*List**/ GetInstruments() = 0;                // Pointer to a List of all instruments
};

#endif // _MusicInfo_h_
