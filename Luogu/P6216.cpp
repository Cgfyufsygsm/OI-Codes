#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 3e6 + 5;
typedef unsigned uint;

inline int min(int a, int b) {return a < b ? a : b;}

char s1[maxn], s2[maxn];
int n, m, fail[maxn];
uint sum[maxn], sumi[maxn], a[maxn];
int len[maxn];

uint ans = 0;

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
        if (j == m) j = fail[j], a[i - m + 1] = 1;
    }
    FOR(i, 1, n) sum[i] = sum[i - 1] + a[i], sumi[i] = sumi[i - 1] + a[i] * i;
    s1[0] = '#', s1[n + 1] = '&';
    for (int i = 1, r = 0, mid = 0; i <= n; ++i)
    {
        if (i <= r) len[i] = min(len[(mid << 1) - i], r - i + 1);
        while (s1[i - len[i]] == s1[i + len[i]]) ++len[i];
        if (i + len[i] > r) r = i + len[i] - 1, mid = i;
    }
    FOR(i, 1, n)
    {
        int l = i - len[i] + 1, r = i + len[i] - m;
        if (l > r) continue;
        int mid = (l + r) >> 1;
        ans += (sumi[mid] - sumi[l - 1]) - (l - 1) * (sum[mid] - sum[l - 1]);
        if (mid != r) ans += (r + 1) * (sum[r] - sum[mid]) - (sumi[r] - sumi[mid]);
    }
    printf("%u\n", ans);
    return 0;
}