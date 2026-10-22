#include "SoundEx.h"
#include <cctype>

using namespace std;

static char SoundexCode(char c)
{
    switch (c)
    {
        case 'B': case 'F': case 'P': case 'V': return '1';
        case 'C': case 'G': case 'J': case 'K':
        case 'Q': case 'S': case 'X': case 'Z': return '2';
        case 'D': case 'T': return '3';
        case 'L': return '4';
        case 'M': case 'N': return '5';
        case 'R': return '6';
        default: return '0';        //samoglasnici, H,W,Y
    }
}

string SoundEx::encode(const string& txt)
{
    if (txt.empty()) return "";

    string kod;
    kod += toupper(txt[0]);

    char prev = SoundexCode(toupper(txt[0]));

    for (int i = 1; i < txt.size(); i++)
    {
        char c = toupper(txt[i]);
        char txt = SoundexCode(c);

        if (txt != '0' && txt != prev)
            kod += txt;

        prev = txt;
    }

    while ((int)kod.size() < 4)
        kod += '0';

    if ((int)kod.size() > 4)
        kod = kod.substr(0, 4);

    return kod;
}
