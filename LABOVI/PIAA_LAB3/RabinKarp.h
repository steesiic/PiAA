#pragma once
#include <vector>
#include <string>
using namespace std;

struct HashPair
{
    int h1;
    int h2;
};

class RabinKarp
{
private:
    const int mod1 = 1000000007;
    const int mod2 = 1000000009;
    const int base1 = 257;
    const int base2 = 263;

    vector<int> hash1, hash2;
    vector<int> power1, power2;
    string text;

    int add(int a, int b, int mod) const;
    int sub(int a, int b, int mod) const;
    int mul(int a, int b, int mod) const;
    int charToInt(unsigned char c) const;

public:
    RabinKarp(const string& s);

    HashPair getSubHash(int l, int r) const;

    vector<int> search(const string& pattern) const;
};
