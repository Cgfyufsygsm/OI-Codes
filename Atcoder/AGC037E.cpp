#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 5005;

int n, k;
char s[maxn << 1];

int l[maxn], maxl;

inline int max(int a, int b) {return a > b ? a : b;}
inline int min(int a, int b) {return a < b ? a : b;}

int cmp(int a, int b)
{
    FOR(i, 1, n)
    {
        if (s[a - i + 1] < s[b - i + 1]) return 1;
        if (s[a - i + 1] > s[b - i + 1]) return 2;
    }
    return 0;
}

int main()
{
    scanf("%d %d", &n, &k);
    scanf("%s", s + 1);
    FOR(i, 1, n) s[n * 2 - i + 1] = s[i];
    int pos = n;
    FOR(i, n + 1, n << 1) if (cmp(i, pos) == 1) pos = i;
    --k;
    int len = 1;
    while (s[pos - len] == s[pos] && len < n) ++len;
    int tmp = len;
    int need = 0;
    while (len < n && need < k) len <<= 1, ++need;
    if (len >= n) for (int i = 1; i <= n; ++i) putchar(s[pos]);
    else
    {
        FOR(i, 1, len) putchar(s[pos]);
        FOR(i, 1, n - len) putchar(s[pos - tmp + 1 - i]);
    }
    return 0;
}