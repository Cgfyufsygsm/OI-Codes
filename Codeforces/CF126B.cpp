#include <cstdio>
#include <cstring>

const int maxn = 1e6 + 5;
char s[maxn];
int n, fail[maxn], maxfail;

inline int max(int a, int b) {return a > b ? a : b;}

int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && s[j + 1] != s[i])
            j = fail[j];
        if (s[j + 1] == s[i]) ++j;
        fail[i] = j;
        if (i != n) maxfail = max(fail[i], maxfail);
    }
    int x = fail[n];
    if (!x) puts("Just a legend");
    else
    {
        while (x > maxfail) x = fail[x];
        if (!x)
        {
            puts("Just a legend");
            return 0;
        }
        for (int i = 1; i <= x; ++i) putchar(s[i]);
    }
    return 0;
}