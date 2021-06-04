#include <cstdio>
#include <bitset>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 21;

inline int max(int a, int b) {return a > b ? a : b;}

int a[maxn];

int popcount(int n)
{
    int ret = 0;
    while (n) ret += (n & 1), n >>= 1;
    return ret;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    FOR(i, 1, n) scanf("%d", a + i);
    int ans = 0;
    FOR(i, 1, (1 << n) - 1)
    {
        if (popcount(i) == n - m)
        {
            std::bitset<2005> s;
            s[0] = 1;
            FOR(j, 1, n) if (i & (1 << (j - 1))) s |= s << a[j];
            ans = max(ans, s.count() - 1);
        }
    }
    printf("%d\n", ans);
}