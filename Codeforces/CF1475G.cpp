#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 2e5 + 5;
int n, cnt[maxn], f[maxn];

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

int main()
{
    int T = read();
    while (T--)
    {
        memset(cnt, 0, sizeof cnt);
        memset(f, 0, sizeof f);
        n = read();
        FOR(i, 1, n) ++cnt[read()];
        FOR(i, 1, maxn)
        {
            f[i] += cnt[i];
            for (int j = 2 * i; j < maxn; j += i)
                f[j] = max(f[i], f[j]);
        }
        printf("%d\n", n - *std::max_element(f + 1, f + maxn));
    }
    return 0;
}