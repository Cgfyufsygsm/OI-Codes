#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define YES printf("YES\n")
#define NO printf("NO\n")
#define int long long

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

const int maxn = 1e5 + 5;

int A, B, n;

struct monster
{
    int a, b;
} a[maxn];

bool cmp(monster x, monster y)
{
    return x.a < y.a;
}

signed main()
{
    int T = read();
    while (T--)
    {
        A = read(), B = read(), n = read();
        FOR(i, 1, n) a[i].a = read();
        FOR(i, 1, n) a[i].b = read();
        std::sort(a + 1, a + n + 1, cmp);
        FOR(i, 1, n)
        {
            int times = a[i].b / A;
            if (a[i].b % A) times++;
            if (i == n) --times;
            B -= a[i].a * times;
        }
        if (B > 0) YES;
        else NO;
    }
    return 0;
}