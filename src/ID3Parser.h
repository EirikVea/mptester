#ifndef _ID3Parser_h_
#define _ID3Parser_h_

#include <iostream>
#include <string>

#include "bass.h"
#include "MusicInfo.h"

using namespace std;

enum
{
    ID3_GENRE_BLUES = 0,
    ID3_GENRE_CLASSIC_ROCK,
    ID3_GENRE_COUNTRY,
    ID3_GENRE_DANCE,
    ID3_GENRE_DISCO,
    ID3_GENRE_FUNK,
    ID3_GENRE_GRUNGE,
    ID3_GENRE_HIP_HOP,
    ID3_GENRE_JAZZ,
    ID3_GENRE_METAL,
    ID3_GENRE_NEW_AGE,
    ID3_GENRE_OLDIES,
    ID3_GENRE_OTHER,
    ID3_GENRE_POP,
    ID3_GENRE_RNB,
    ID3_GENRE_RAP,
    ID3_GENRE_REGGAE,
    ID3_GENRE_ROCK,
    ID3_GENRE_TECHNO,
    ID3_GENRE_INDUSTRIAL,
    ID3_GENRE_ALTERNATIVE,
    ID3_GENRE_SKA,
    ID3_GENRE_DEATH_METAL,
    ID3_GENRE_PRANKS,
    ID3_GENRE_SOUNDTRACK,
    ID3_GENRE_EURO_TECHNO,
    ID3_GENRE_AMBIENT,
    ID3_GENRE_TRIP_HOP,
    ID3_GENRE_VOCAL,
    ID3_GENRE_JAZZ_FUNK,
    ID3_GENRE_FUSION,
    ID3_GENRE_TRANCE,
    ID3_GENRE_CLASSICAL,
    ID3_GENRE_INSTRUMENTAL,
    ID3_GENRE_ACID,
    ID3_GENRE_HOUSE,
    ID3_GENRE_GAME,
    ID3_GENRE_SOUND_CLIP,
    ID3_GENRE_GOSPEL,
    ID3_GENRE_NOISE,
    ID3_GENRE_ALTERNROCK,
    ID3_GENRE_BASS,
    ID3_GENRE_SOUL,
    ID3_GENRE_PUNK,
    ID3_GENRE_SPACE,
    ID3_GENRE_MEDITATIVE,
    ID3_GENRE_INSTRUMENTAL_POP,
    ID3_GENRE_INSTRUMENTAL_ROCK,
    ID3_GENRE_ETHNIC,
    ID3_GENRE_GOTHIC,
    ID3_GENRE_DARKWAVE,
    ID3_GENRE_TECHNO_INDUSTRIAL,
    ID3_GENRE_ELECTRONIC,
    ID3_GENRE_POP_FOLK,
    ID3_GENRE_EURODANCE,
    ID3_GENRE_DREAM,
    ID3_GENRE_SOUTHERN_ROCK,
    ID3_GENRE_COMEDY,
    ID3_GENRE_CULT,
    ID3_GENRE_GANGSTA,
    ID3_GENRE_TOP_40,
    ID3_GENRE_CHRISTIAN_RAP,
    ID3_GENRE_POP_FUNK,
    ID3_GENRE_JUNGLE,
    ID3_GENRE_NATIVE_AMERICAN,
    ID3_GENRE_CABARET,
    ID3_GENRE_NEW_WAVE,
    ID3_GENRE_PSYCHADELIC,
    ID3_GENRE_RAVE,
    ID3_GENRE_SHOWTUNES,
    ID3_GENRE_TRAILER,
    ID3_GENRE_LO_FI,
    ID3_GENRE_TRIBAL,
    ID3_GENRE_ACID_PUNK,
    ID3_GENRE_ACID_JAZZ,
    ID3_GENRE_POLKA,
    ID3_GENRE_RETRO,
    ID3_GENRE_MUSICAL,
    ID3_GENRE_ROCK_AND_ROLL,
    ID3_GENRE_HARD_ROCK,
    //Winamp extensions
    ID3_GENRE_FOLK,
    ID3_GENRE_FOLK_ROCK,
    ID3_GENRE_NATIONAL_FOLK,
    ID3_GENRE_SWING,
    ID3_GENRE_FAST_FUSION,
    ID3_GENRE_BEBOB,
    ID3_GENRE_LATIN,
    ID3_GENRE_REVIVAL,
    ID3_GENRE_CELTIC,
    ID3_GENRE_BLUEGRASS,
    ID3_GENRE_AVANTGARDE,
    ID3_GENRE_GOTHIC_ROCK,
    ID3_GENRE_PROGRESSIVE_ROCK,
    ID3_GENRE_PSYCHEDELIC_ROCK,
    ID3_GENRE_SYMPHONIC_ROCK,
    ID3_GENRE_SLOW_ROCK,
    ID3_GENRE_BIG_BAND,
    ID3_GENRE_CHORUS,
    ID3_GENRE_EASY_LISTENING,
    ID3_GENRE_ACOUSTIC,
    ID3_GENRE_HUMOUR,
    ID3_GENRE_SPEECH,
    ID3_GENRE_CHANSON,
    ID3_GENRE_OPERA,
    ID3_GENRE_CHAMBER_MUSIC,
    ID3_GENRE_SONATA,
    ID3_GENRE_SYMPHONY,
    ID3_GENRE_BOOTY_BASS,
    ID3_GENRE_PRIMUS,
    ID3_GENRE_PORN_GROOVE,
    ID3_GENRE_SATIRE,
    ID3_GENRE_SLOW_JAM,
    ID3_GENRE_CLUB,
    ID3_GENRE_TANGO,
    ID3_GENRE_SAMBA,
    ID3_GENRE_FOLKLORE,
    ID3_GENRE_BALLAD,
    ID3_GENRE_POWER_BALLAD,
    ID3_GENRE_RHYTHMIC_SOUL,
    ID3_GENRE_FREESTYLE,
    ID3_GENRE_DUET,
    ID3_GENRE_PUNK_ROCK,
    ID3_GENRE_DRUM_SOLO,
    ID3_GENRE_A_CAPELLA,
    ID3_GENRE_EURO_HOUSE,
    ID3_GENRE_DANCE_HALL
};

const string ID3_GENRES[] =
{
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
    //Winamp extensions
    "Folk",
    "Folk-Rock",
    "National Folk",
    "Swing",
    "Fast Fusion",
    "Bebob",
    "Latin",
    "Revival",
    "Celtic",
    "Bluegrass",
    "Avantgarde",
    "Gothic Rock",
    "Progressive Rock",
    "Psychedelic Rock",
    "Symphonic Rock",
    "Slow Rock",
    "Big Band",
    "Chorus",
    "Easy Listening",
    "Acoustic",
    "Humour",
    "Speech",
    "Chanson",
    "Opera",
    "Chamber Music",
    "Sonata",
    "Symphony",
    "Booty Bass",
    "Primus",
    "Porn Groove",
    "Satire",
    "Slow Jam",
    "Club",
    "Tango",
    "Samba",
    "Folklore",
    "Ballad",
    "Power Ballad",
    "Rhythmic Soul",
    "Freestyle",
    "Duet",
    "Punk Rock",
    "Drum Solo",
    "A capella",
    "Euro-House",
    "Dance Hall"
};

class ID3Parser
{
    private:
        DWORD ID3_version;

        struct _ID3V1
        {
            string title;   // Song title
            string artist;  // Artist name
            string album;   // Album title
            string year;    // Year
            string comment; // Comment
            string genre;   // Genre
            int track_no;   // Track number
        } ID3V1;

        // Ref. ID3v2.4.0 specification, section 4.2. 'Text information frames'
        typedef struct ID3V2STR
        {
            BYTE encoding;  // Text encoding
            string text;    // Text string according to encoding
        } _ID3V2STR;

        struct _ID3V2
        {
            string UFID;    // Ref. ID3v2.4.0 specification, section 4.1. 'Unique file identifier'

            // Ref. ID3v2.4.0 specification, section 4.2.1. 'Identification frames'
            ID3V2STR TIT1;  // Content group description
            ID3V2STR TIT2;  // Title/Songname/Content description
            ID3V2STR TIT3;  // Subtitle/Description refinement
            ID3V2STR TALB;  // Album/Movie/Show title
            ID3V2STR TOAL;  // Original album/movie/show title
            ID3V2STR TRCK;  // Track number/Position in set
            ID3V2STR TPOS;  // Part of a set
            ID3V2STR TSST;  // Set subtitle
            ID3V2STR TRSC;  // International Standard Recording Code [ISRC] (12 characters)

            // Ref. ID3v2.3.0 specification, section 4.2.1. 'Identification frames'
            ID3V2STR TYER;  // Year (deprecated in ID3v2.4.0)

            // Ref. ID3v2.4.0 specification, section 4.2.2. 'Involved persons frames'
            ID3V2STR TPE1;  // Lead artist/Lead performer/Soloist/Performing group
            ID3V2STR TPE2;  // Band/Orchestra/Accompaniment
            ID3V2STR TPE3;  // Conductor
            ID3V2STR TPE4;  // Interpreted, remixed, or otherwise modified by
            ID3V2STR TOPE;  // Original artist/performer
            ID3V2STR TEXT;  // Lyricist/Text writer
            ID3V2STR TOLY;  // Original lyricist/text writer
            ID3V2STR TCOM;  // Composer
            ID3V2STR TMCL;  // Musician credits list
            ID3V2STR TIPL;  // Involved people list
            ID3V2STR TENC;  // Encoded by

            // Ref. ID3v2.4.0 specification, section 4.2.3. 'Derived and subjective properties frames'
            ID3V2STR TBPM;  // BPM
            ID3V2STR TLEN;  // Length (milliseconds)
            ID3V2STR TKEY;  // Initial key
            ID3V2STR TLAN;  // Language according to ISO-639-2
            ID3V2STR TCON;  // Content type (ID3v1 genre or custom string)
            ID3V2STR TFLT;  // File type
            ID3V2STR TMED;  // Media type
            ID3V2STR TMOO;  // Mood

            // Ref. ID3v2.4.0 specification, section 4.2.4. 'Rights and license frames'
            ID3V2STR TCOP;  // Copyright message
            ID3V2STR TPRO;  // Produced notice
            ID3V2STR TPUB;  // Publisher
            ID3V2STR TOWN;  // File owner/licensee
            ID3V2STR TRSN;  // Internet radio station name
            ID3V2STR TRSO;  // Internet radio station owner

            // Ref. ID3v2.4.0 specification, section 4.2.5. 'Other text frames'
            ID3V2STR TOFN;  // Original filename
            ID3V2STR TDLY;  // Playlist delay
            ID3V2STR TDEN;  // Encoding time
            ID3V2STR TDOR;  // Original release time
            ID3V2STR TDRC;  // Recording time
            ID3V2STR TDRL;  // Release time
            ID3V2STR TDTG;  // Tagging time
            ID3V2STR TSSE;  // Software/Hardware and settings used for encoding
            ID3V2STR TSOA;  // Album sort order
            ID3V2STR TSOT;  // Title sort order
            ID3V2STR TXXX;  // User defined text information frame

            // Ref. ID3v2.4.0 specification, section 4.3.1. 'URL link frames - details'
            string WCOM;    // Commercial information
            string WCOP;    // Copyright/Legal information
            string WOAF;    // Official audio file webpage
            string WOAR;    // Official artist/performer webpage
            string WOAS;    // Official audio source webpage
            string WORS;    // Official Internet radio station homepage
            string WPAY;    // Payment
            string WPUB;    // Publishers official webpage
            string WXXX;    // User defined URL link frame

            // Ref. ID3v2.4.0 specification, section 4.4. 'Music CD identifier'
            // TODO: Implement MCDI

            // Ref. ID3v2.4.0 specification, section 4.5. 'Event timing codes'
            // TODO: Implement ETCO

            // Ref. ID3v2.4.0 specification, section 4.6. 'MPEG location lookup table'
            // TODO: Implement MLLT

            // Ref. ID3v2.4.0 specification, section 4.7. 'Synchronised tempo codes'
            // TODO: Implement SYTC

            // Ref. ID3v2.4.0 specification, section 4.8. 'Unsynchronised lyrics/text transcription'
            // TODO: Implement USLT

            // Ref. ID3v2.4.0 specification, section 4.9. 'Synchronised lyrics/text'
            // TODO: Implement SYLT

            // Ref. ID3v2.4.0 specification, section 4.10. 'Comments'
            struct _COMM
            {
                BYTE encoding;  // Text encoding
                char lang[3];   // Language
                string desc;    // Short content description
                string text;    // The actual text
            } COMM;

            // Ref. ID3v2.4.0 specification, section 4.11. 'Relative volume adjustment (2)'
            //TODO: Implement RVA2

            // Ref. ID3v2.4.0 specification, section 4.12. 'Equalisation (2)'
            //TODO: Implement EQU2

            // Ref. ID3v2.4.0 specification, section 4.13. 'Reverb'
            struct _RVRB
            {
                WORD left;      // Reverb left (ms)
                WORD right;     // Reverb right (ms)
                BYTE bnc_left;  // Reverb bounces, left
                BYTE bnc_right; // Reverb bounces, right
                BYTE fdb_ltol;  // Reverb feedback, left to left
                BYTE fdb_ltor;  // Reverb feedback, left to right
                BYTE fdb_rtor;  // Reverb feedback, right to right
                BYTE fdb_rtol;  // Reverb feedback, right to left
                BYTE pmx_ltor;  // Premix left to right
                BYTE pmx_rtol;  // Premix right to left
            } RVRB;

            struct _APIC
            {
                BYTE encoding;  // Text encoding
                string MIME;    // MIME type
                BYTE pictype;   // Picture type
                string desc;    // Description
                char *bits;     // Picture data
            } APIC;

            // Ref. ID3v2.4.0 specification, section 4.15. 'General encapsulated object'
            struct _GEOB
            {
                BYTE encoding;  // Text encoding
                string MIME;    // MIME type
                string fname;   // Filename
                string desc;    // Content description
                char *obj;      // Encapsulated object
            } GEOB;

            DWORD PCNT;     // Ref. ID3v2.4.0 specification, section 4.16. 'Play counter'

            // Ref. ID3v2.4.0 specification, section 4.17. 'Popularimeter'
            struct _POPM
            {
                string email;   // Email to user
                BYTE rating;    // Rating
                DWORD counter;  // Counter
            } POPM;

            // Ref. ID3v2.4.0 specification, section 4.18. 'Recommended buffer size'
            struct _RBUF
            {
                union _BUFSZ
                {
                    BYTE sz1; // Buffer size
                    BYTE sz2; // Buffer size
                    BYTE sz3; // Buffer size
                    BYTE flg; // Embedded info flag
                } BUFSZ;
                DWORD offset;   //Offset to next tag
            } RBUF;

            // Ref. ID3v2.4.0 specification, section 4.19. 'Audio encryption'
            struct _AENC
            {
                string owner_id;    // Owner identifier
                WORD pw_start;      // Preview start
                WORD pw_len;        // Preview end
                char *enc_inf;      // Encryption info
            } AENC;

            // Ref. ID3v2.4.0 specification, section 4.20. 'Linked information'
            struct _LINK
            {
                char id[4];     // Frame identifier
                string url;     // URL
                string **add;   // ID and additional data
            } LINK;

            // Ref. ID3v2.4.0 specification, section 4.21. 'Position synchronisation frame'
            //TODO: Implement POSS

            string USER;    // Ref. ID3v2.4.0 specification, section 4.22. 'Terms of use frame'
            string COMR;    // Ref. ID3v2.4.0 specification, section 4.24. 'Commercial frame'

            // Ref. ID3v2.4.0 specification, section 4.25. 'Encryption method registration'
            //TODO: Implement ENCR

            // Ref. ID3v2.4.0 specification, section 4.26. 'Group identification registration'
            //TODO: Implement GRID

            // Ref. ID3v2.4.0 specification, section 4.27. 'Private frame'
            //TODO: Implement PRIV

            // Ref. ID3v2.4.0 specification, section 4.28. 'Signature frame'
            //TODO: Implement SIGN
            DWORD SEEK;     // Ref. ID3v2.4.0 specification, section 4.29. 'Seek frame'

            // Ref. ID3v2.4.0 specification, section 4.30. 'Audio seek point index'
            //TODO: Implement ASPI
        } ID3V2;

        bool _GetID3v2String(const char *pframes, ID3V2STR& frame, const char search_key[]);
        void _ParseID3v2String(char *pframes, int pos, int size, ID3V2STR& out);
    public:
        ID3Parser(HSTREAM h, MusicInfo &mi);
        ~ID3Parser();

        // General info
        DWORD GetVersion();
        bool IsValid();

        string const& GetTitle();
        string const& GetArtist();
        string const& GetAlbum();
        string const& GetYear();
        string const& GetGenre();
        string const& GetComment();

        string const& GetID3v2TextFrame(const char frame[]);
};

#endif // _ID3Parser_h_
