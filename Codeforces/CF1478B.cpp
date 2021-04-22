#include <cstdio>
#include <cctype>
#include <cstring>
#define init(a) memset((a), 0, sizeof (a))
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define YES printf("YES\n")
#define NO printf("NO\n")

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

int can[105][10], luck[105][10], cnt;

int main()
{
    int T = read();
    FOR(d, 1, 9)
    {
        cnt = 0;
        FOR(i, d, 90)
        {
            if (i % d == 0 || (i / 10) == d || can[i][d] || (i % 10 == d))
            {
                can[i][d] = 1, luck[++cnt][d] = i;
                FOR(j, 1, cnt)
                    for(int k = 1; i + k * luck[j][d] < 100; ++k)
                        can[i + k * luck[j][d]][d] = 1;
            }
        }
    }
    while (T--)
    {
        int q = read(), d = read();
        FOR(i, 1, q)
        {
            int tmp = read();
            if (tmp >= 10 * d) YES;
            else if (can[tmp][d]) YES;
            else NO;
        }
    }
    return 0;
}