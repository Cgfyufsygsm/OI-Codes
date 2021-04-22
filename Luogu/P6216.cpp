#include <cstdio>
#define int unsigned

const int maxn = 3e6 + 5;

char s1[maxn], s2[maxn];
int n, m, fail[maxn];
int cnt[maxn];

signed main()
{
    scanf("%u %u", &n, &m);
    scanf("%s %s", s1 + 1, s2 + 1);
    for (int i = 2, j = 0; i <= m; ++i)
    {
        while (j && s2[j + 1] != s2[i]) j = fail[j];
        if (s2[j + 1] == s2[i]) ++j;
        fail[i] = j;
    }
    for (int i = 1, j = 0; i <= n; ++i)
    {
        while (j && s2[j + 1] != s1[i]) j = fail[j];
        if (s2[j + 1] == s1[i]) ++j;
        if (j == m) cnt[i] = 1, j = fail[j];
        cnt[i] += cnt[i - 1];
    }
    s1[0] = '#', s1[n + 1] = '&';

}