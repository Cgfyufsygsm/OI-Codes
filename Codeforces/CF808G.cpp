#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e5 + 5;
char s[maxn], t[maxn];
int n, m;

int f[maxn], g[maxn], fail[maxn];

inline int max(int a, int b) {return a > b ? a : b;}

bool check(int p)
{
    FOR(i, 1, m)
        if (s[p - m + i] != t[i] && s[p - m + i] != '?')
            return false;
    return true;
}

int main()
{
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && t[j + 1] != t[i]) j = fail[j];
        if (t[j + 1] == t[i]) ++j;
        fail[i] = j;
    }
    FOR(i, m, n)
    {
        f[i] = f[i - 1];
        if (check(i))
        {
            g[i] = f[i - m] + 1;
            for (int j = fail[m]; j; j = fail[j])
                g[i] = max(g[i], g[i - (m - j)] + 1);
        }
        f[i] = max(f[i], g[i]);
    }
    printf("%d\n", f[n]);
    return 0;
}