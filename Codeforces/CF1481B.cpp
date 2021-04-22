#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

const int maxn = 105;

int n, k;
int h[maxn];

int main()
{
    int T = read();
    while (T--)
    {
        n = read(), k = read();
        FOR(i, 1, n) h[i] = read();
        int stop = 1;
        h[n + 1] = 1e9;
        int ans = -1;
        while (stop != n)
        {
            int rem = 0;
            FOR(i, 1, n)
            {
                if (h[i] < h[i + 1])
                {
                    stop = i;
                    break;
                }
            }
            if (stop == n) break;
            FOR(i, 1, stop)
                if (h[i] < h[stop + 1])
                    rem += h[stop + 1] - h[i];
            if (k <= rem)
            {
                FOR(i, 1, k)
                {
                    FOR(j, 1, stop)
                    {
                        if (h[j] < h[j + 1])
                        {
                            if (i == k)
                                ans = j;
                            ++h[j];
                            break;
                        }
                    }
                    if (ans != -1) break;
                }
                break;
            }
            else
            {
                k -= rem;
                FOR(i, 1, stop)
                    if (h[i] < h[stop + 1])
                        h[i] = h[stop + 1];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}