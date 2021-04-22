#include <cstdio>
#include <cctype>
#include <map>
#include <algorithm>
#define reg register
#define il inline
#define FOR(i, a, b) for (reg signed i = a; i <= b; ++i)

il int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

il int max(int a, int b) {return a > b ? a : b;}
il int min(int a, int b) {return a < b ? a : b;}

const int maxn = 1000000 + 5;
int n, a[maxn], b[maxn];
int f[maxn], maxa, ans = maxn << 2;

std::map<int, bool> mp;
std::map<int, int> power;

int main()
{
    n = read();
    FOR(i, 1, n)
    {
        a[i] = read(), b[i] = read();
        power[a[i]] = b[i];
        mp[a[i]] = 1;
        maxa = max(maxa, a[i]);
    }
    if (mp[0]) f[0] = 1;
    FOR(i, 0, maxa)
    {
        if (mp[i])
        {
            int p = power[i];
            if (p >= i)
                f[i] = 1;
            else f[i] = f[i - p - 1] + 1;
        }
        else f[i] = f[i - 1];
        ans = min(ans, n - f[i]);
    }
    printf("%d\n", ans);
}