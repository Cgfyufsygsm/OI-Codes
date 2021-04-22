#include <cstdio>
#include <cctype>
#include <set>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 1e5 + 5;
int n, a[maxn], pre[maxn], suf[maxn], pos[maxn];

int main()
{
    n = read();
    FOR(i, 1, n)
        a[i] = read();
    FOR(i, 1, n)
        if (a[i] > a[i - 1])
            pre[i] = pre[i - 1] + 1;
        else pre[i] = 1;
    DEC(i, n, 1)
        if (a[i] > a[i + 1])
            suf[i] = suf[i + 1] + 1;
        else suf[i] = 1;
    int maxlen = 0, cnt = 0;
    bool flag = 0;
    FOR(i, 1, n)
        maxlen = max(max(maxlen, pre[i]), suf[i]);
    FOR(i, 1, n)
    {
        if (pre[i] == maxlen)
            ++cnt;
        if (suf[i] == maxlen)
            ++cnt;
        if (i + maxlen - 1 <= n && i - maxlen + 1 >= 1 && suf[i] == maxlen && pre[i] == maxlen)
            flag = 1;
    }
    if (cnt == 2 && flag)
    {
        printf("%d\n", maxlen & 1);
        return 0;
    }
    else puts("0");
    return 0;
}