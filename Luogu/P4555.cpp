#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

inline int max(int a, int b) {return a > b ? a : b;}
inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 1e5 + 5;

char s[maxn << 1], real[maxn];
int n, len[maxn << 1], cnt;
int fl[maxn << 1], fr[maxn << 1];

int main()
{
    scanf("%s", real + 1);
    n = strlen(real + 1);
    s[cnt = 0] = '&', s[++cnt] = '#';
    FOR(i, 1, n) s[++cnt] = real[i], s[++cnt] = '#';
    for (int i = 1, r = 0, mid = 0; i <= cnt; ++i)
    {
        if (i <= r) len[i] = min(len[(mid << 1) - i], r - i + 1);
        while (s[i - len[i]] == s[i + len[i]]) ++len[i];
        if (i + len[i] > r) r = i + len[i] - 1, mid = i;
        fl[i + len[i] - 1] = max(fl[i + len[i] - 1], len[i] - 1);
        fr[i - len[i] + 1] = max(fr[i - len[i] + 1], len[i] - 1);
    }
    FOR(i, 1, cnt) fr[i] = max(fr[i], fr[i - 2] - 2);
    DEC(i, cnt, 1) fl[i] = max(fl[i], fl[i + 2] - 2);
    int ans = 0;
    for (int i = 1; i < cnt; i += 2) if (fl[i] && fr[i]) ans = max(fl[i] + fr[i], ans);
    printf("%d\n", ans);
    return 0;
}
