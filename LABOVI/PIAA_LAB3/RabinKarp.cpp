#include "RabinKarp.h"

int RabinKarp::add(int a, int b, int mod) const
{
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int RabinKarp::sub(int a, int b, int mod) const
{
    a -= b;
    if (a < 0) a += mod;
    return a;
}

int RabinKarp::mul(int a, int b, int mod) const
{
    return (int)((1LL * a * b) % mod);
}

int RabinKarp::charToInt(unsigned char c) const
{
    return (int)c + 1;
}

RabinKarp::RabinKarp(const string& s) : text(s)
{
    int n = s.size();
    hash1.resize(n);
    hash2.resize(n);
    power1.resize(n);
    power2.resize(n);

    hash1[0] = charToInt(s[0]);
    hash2[0] = charToInt(s[0]);
    power1[0] = 1;
    power2[0] = 1;

    for (int i = 1; i < n; i++)
    {
        hash1[i] = add(mul(hash1[i - 1], base1, mod1), charToInt(s[i]), mod1);
        power1[i] = mul(power1[i - 1], base1, mod1);

        hash2[i] = add(mul(hash2[i - 1], base2, mod2), charToInt(s[i]), mod2);
        power2[i] = mul(power2[i - 1], base2, mod2);
    }
}

HashPair RabinKarp::getSubHash(int l, int r) const
{
    int h1 = hash1[r];
    int h2 = hash2[r];

    if (l > 0)
    {
        h1 = sub(h1, mul(hash1[l - 1], power1[r - l + 1], mod1), mod1);
        h2 = sub(h2, mul(hash2[l - 1], power2[r - l + 1], mod2), mod2);
    }

    return { h1, h2 };
}

vector<int> RabinKarp::search(const string& pattern) const
{
    vector<int> result;
    int n = text.size();
    int m = pattern.size();

    if (m > n || m == 0)
        return result;

    int pHash1 = 0, pHash2 = 0;
    for (char c : pattern)
    {
        pHash1 = add(mul(pHash1, base1, mod1), charToInt(c), mod1);
        pHash2 = add(mul(pHash2, base2, mod2), charToInt(c), mod2);
    }

    for (int i = 0; i <= n - m; i++)
    {
        HashPair h = getSubHash(i, i + m - 1);

        if (h.h1 == pHash1 && h.h2 == pHash2)
        {
            if (text.substr(i, m) == pattern)
                result.push_back(i);
        }
    }

    return result;
}
