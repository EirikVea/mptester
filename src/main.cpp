#include <conio.h>
#include <windows.h>

#include "MusicPlayer.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc < 2)
        return -1;

    string file = argv[1];

    cout << endl << endl
            << "*******************************************************************" << endl
            << "********************    Music Player tester    ********************" << endl
            << "*******************************************************************" << endl
            << endl;

    MusicPlayer mp(44100);

    if(mp.Load(file))
        cout << "Tune successfully loaded:" << endl;
    else
        cout << "Tune not supported!" << endl;

    mp.Play();

    cout << "\tFile:     " << mp.GetFileName() << endl;
    cout << "\tFormat:   " << mp.GetFormat() << endl;
    cout << "\tTitle:    " << mp.GetSongName() << endl;
    cout << "\tArtist:   " << mp.GetArtistName() << endl;
    cout << "\tAlbum:    " << mp.GetAlbumName() << endl;
    cout << "\tYear:     " << mp.GetYear() << endl;
    cout << "\tGenre:    " << mp.GetGenre() << endl;
    cout << "\tComment:  " << mp.GetComment() << endl;
    cout << "\tDuration: " << dec << mp.GetLengthMS() << "ms" << endl;

    while(mp.IsPlaying())
    {
        if(kbhit())
        {
            char ch = getch();
            switch(ch)
            {
                case 'n':
                    mp.NextSubsong();
                    break;
                case 'p':
                    mp.PrevSubsong();
                    break;
                default:
                    return 0;
                    break;
            }
        }
    }

    return 0;
}
