#include <cstdio>
#include <cctype>
#include <map>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 2e5 + 5;
typedef long long ll;

int a[maxn];

int main()
{
    int n = read();
    FOR(i, 1, n) a[i] = read();
    std::map<ll, int> mp;
    ll s = 0, ans = 0;
    mp[0] = 1;
    FOR(i, 1, n)
        s += a[i], ans += mp[s], mp[s]++;
    printf("%lld\n", ans);
    return 0;
}