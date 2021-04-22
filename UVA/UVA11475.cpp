#include <cstdio>
#include <cstring>

const int maxn = 1e5 + 5;

char s0[maxn], s[maxn << 1];
int len[maxn << 1], cnt;

inline int min(int a, int b) {return a < b ? a : b;}

int main()
{
    while (~scanf("%s", s0 + 1))
    {
        s[0] = '&', s[cnt = 1] = '#', len[0] = 0;
        int n = strlen(s0 + 1), ans = 1;
        for (int i = 1; i <= n; ++i) s[++cnt] = s0[i], s[++cnt] = '#';
        for (int i = 1, r = 0, mid = 0; i <= cnt; ++i)
        {
            len[i] = 0;
            if (i <= r)
                len[i] = min(len[(mid << 1) - i], r - i + 1);
            while (s[i - len[i]] == s[i + len[i]]) ++len[i];
            if (i + len[i] > r) r = i + len[i] - 1, mid = i;
            if (i + len[i] - 1 == cnt)
            {
                ans = len[i] - 1;
                break;
            }
        }
        printf("%s", s0 + 1);
        for (int i = n - ans; i >= 1; --i) putchar(s0[i]);
        puts("");
    }
    return 0;
}