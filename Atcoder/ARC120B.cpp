#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

const int maxn = 505;
const ll mod = 998244353;

int h, w;
char s[maxn][maxn];
int r[maxn << 1], b[maxn << 1];

int main()
{
    scanf("%d %d", &h, &w);
    FOR(i, 1, h) scanf("%s", s[i] + 1);
    ll ans = 1;
    FOR(i, 1, h)
        FOR(j, 1, w)
            if (s[i][j] == 'R')  ++r[i + j];
            else if (s[i][j] == 'B') ++b[i + j];
    FOR(i, 2, h + w)
        if (r[i] && !b[i]) ans *= 1ll;
        else if (b[i] && !r[i]) ans *= 1ll;
        else if (!b[i] && !r[i]) ans = ans * 2ll % mod;
        else ans = 0;
    printf("%lld\n", ans);
    return 0;
}