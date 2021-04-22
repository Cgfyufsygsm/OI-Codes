#include <cstdio>
#include <cctype>
#include <cstring>

const int maxn = 1.1e7 + 5;

char s[maxn << 1];
int len[maxn << 1], cnt, ans;

inline int min(int a, int b) {return a < b ? a : b;}

void read()
{
    char c = getchar();
    s[0] = '&', s[cnt = 1] = '#';
    while (!isalpha(c)) c = getchar();
    while (isalpha(c)) s[++cnt] = c, s[++cnt] = '#', c = getchar();
    return;
}

int main()
{
    read();
    for (int i = 1, r = 0, mid = 0; i <= cnt; ++i)
    {
        if (i <= r)
            len[i] = min(len[(mid << 1) - i], r - i + 1);
        while (s[i - len[i]] == s[i + len[i]]) ++len[i];
        if (i + len[i] > r) r = i + len[i] - 1, mid = i;
        if (len[i] > ans) ans = len[i];
    }
    printf("%d\n", ans - 1);
    return 0;
}