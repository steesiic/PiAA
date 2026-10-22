#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "RabinKarp.h"
#include "SoundEx.h"
using namespace std;
using namespace chrono;

string lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing";
string heks = "1a3f5c7e9b0d2f4a6c8e0b1d3f";



string UcitajFajl(const string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "fajl: " << filename <<" ne moze da se otvori"<< endl;
        return "";
    }

    string text, line;
    while (getline(file, line))
        text += line;

    file.close();
    return text;
}


string NapraviAsciiPattern(int len)
{
    string tmp = lorem.substr(0, len);
    return tmp;
}

string NapraviHexPattern(int len)
{
    string tmp = heks.substr(0, len);
    return tmp;
}

void TestRabinKarp(const string& filename,const string& pattern, const string& reportFile)
{
    string text = UcitajFajl(filename);
    if (text.empty()) return;

    RabinKarp rk(text);

    auto start = high_resolution_clock::now();

    vector<int> positions = rk.search(pattern);

    auto end = high_resolution_clock::now();

    milliseconds duration = duration_cast<milliseconds>(end - start);

    cout << "RabinKarp fajl: " << filename
        << ", duzina patterna: " << pattern.size()
        << ", broj: " << positions.size()
        << ", vreme: " << duration.count() << " ms\n";

    ofstream izlaz(reportFile, ios::app);
    izlaz << "fajl: " << filename << "\n";
    izlaz << "pattern: " << pattern << "\n";
    izlaz << "broj pojavljivanja: " << positions.size() << "\n";
    izlaz << "vreme: " << duration.count() << " ms\n";
    izlaz << "----------------------------------\n";
    izlaz.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> ExtractWords(const string& text)
{
    vector<string> words;
    string curr = "";

    for (int i = 0; i < text.size(); i++)
    {
        char c = text[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            curr += c;
        }
        else
        {
            if (!curr.empty())
            {
                words.push_back(curr);
                curr.clear();
            }
        }
    }

    if (!curr.empty())
        words.push_back(curr);

    return words;
}

bool VecPostoji(const vector<string>& v, const string& s)
{
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i] == s)
            return true;
    return false;
}

void TestSoundEx(const string& filename, int patternLen)
{
    string text = UcitajFajl(filename);
    if (text.empty()) return;

    vector<string> words = ExtractWords(text);
    if (words.empty()) return;

    string pattern = words[0].substr(0, patternLen);

    auto start = high_resolution_clock::now();
    string pCode = SoundEx::encode(pattern);

   

    cout << "\nSoundEx fajl: " << filename
        << ", pattern: " << pattern
        << ", kod: " << pCode << "\n";

    ofstream izlaz("reportSoundEx_ASCII.txt", ios::app);

    izlaz << "fajl: " << filename << "\n";
    izlaz << "pattern: " << pattern << "\n";
    izlaz << "SoundEx kod: " << pCode << "\n";
    izlaz << "duzina provere: " << patternLen << " karaktera\n";
    izlaz << "pronadjene reci:\n";

    vector<string> found;

    for (int i = 0; i < words.size(); i++)
    {
        if (words[i].size() >= patternLen)
        {
            string sub = words[i].substr(0, patternLen);

            if (SoundEx::encode(sub) == pCode && sub != pattern)
            {
                if (!VecPostoji(found, sub))
                    found.push_back(sub);
            }
        }
    }
    auto end = high_resolution_clock::now();

    milliseconds duration = duration_cast<milliseconds>(end - start);
    if (found.empty())
    {
        izlaz << "  nema slicnih reci\n";
    }
    else
    {
        for (int i = 0; i < found.size(); i++)
            izlaz << "  -> " << found[i] << "\n";
    }
    izlaz << "vreme: " << duration.count() << " ms\n";
    izlaz << "----------------------------------\n";
    izlaz.close();
}



int main()
{
    vector<string> asciiFiles = 
    {
        "ASCII_100.txt", "ASCII_1000.txt",
        "ASCII_10000.txt", "ASCII_100000.txt"
    };

    vector<string> hexFiles = 
    {
        "hex_100.txt", "hex_1000.txt",
        "hex_10000.txt", "hex_100000.txt"
    };

    vector<string> harryPotter =
    {
        "hp_100.txt", "hp_1000.txt",
        "hp_10000.txt", "hp_100000.txt"
    };

    vector<int> rkPatt = { 5, 10, 20, 50 };

    for (const string& file : asciiFiles)
    {
        for (int len : rkPatt)
        {
            string pattern = NapraviAsciiPattern(len);
            TestRabinKarp(file, pattern, "reportRK_ASCII.txt");
        }
    }

    for (const string& file : hexFiles)
    {
        for (int len : rkPatt)
        {
            string pattern = NapraviHexPattern(len);
            TestRabinKarp(file, pattern, "reportRK_hex.txt");
        }
    }


    vector<int> soundexLengths = { 5, 10, 20 };

    for (int i = 0; i < harryPotter.size(); i++)
    {
        for (int j = 0; j < soundexLengths.size(); j++)
        {
            TestSoundEx(harryPotter[i], soundexLengths[j]);
        }
    }


    cout << "\nSvi testovi zavrseni.\n";
    return 0;
}
