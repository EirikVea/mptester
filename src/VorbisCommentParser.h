#ifndef _VorbisCommentParser_h_
#define _VorbisCommentParser_h_

#include <iostream>
#include <string>

#include "bass.h"
#include "MusicInfo.h"

using namespace std;

class VorbisCommentParser
{
    private:
        string title;   // Song title
        string artist;  // Artist name
        string album;   // Album title
        string year;    // Year
        string comment; // Comment
        string genre;   // Genre

        bool valid;

        bool _GetField(char *comments ,const char fieldname[], string& out);
    public:
        VorbisCommentParser(HSTREAM h, MusicInfo &mi);
        ~VorbisCommentParser();

        bool IsValid();
};

#endif // _VorbisCommentParser_h_
