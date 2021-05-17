#include <cstdio>
#include <cctype>
#include <map>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 3e5 + 5;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

typedef long long ll;

int n;

ll ans, a[maxn], s[maxn];

std::map<ll, ll> m;

int main()
{
    n = read();
    FOR(i, 1, n) a[i] = read() * ((i & 1) ? -1 : 1);
    FOR(i, 1, n) s[i] = a[i] + s[i - 1], ++m[s[i]];
    ++m[0];
    for (std::map<ll, ll>::iterator it = m.begin(); it != m.end(); ++it)
        ans += (*it).second * ((*it).second - 1ll) / 2;
    printf("%lld\n", ans);
    return 0;
}