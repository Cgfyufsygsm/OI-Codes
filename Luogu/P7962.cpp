#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using ll = long long;
const int maxn = 10005, maxa = 605;
const ll INF = 1e18;
ll d[maxn], s[maxn], f[maxn * maxa];
int n, mx, a[maxn];

template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}

int main() {
    scanf("%d", &n);
    FOR(i, 0, n - 1) scanf("%d", a + i), chkmax(mx, a[i]);
    FOR(i, 1, n - 1) d[i] = a[i] - a[i - 1];
    sort(d + 1, d + n);
    FOR(i, 1, n * mx) f[i] = INF;
    f[0] = s[0] = 0;
    FOR(i, 1, n - 1) {
        s[i] = s[i - 1] + d[i];
        if (!d[i]) continue;
        DEC(j, n * mx, 0) {
            if (f[j] >= INF) continue;
            chkmin(f[j + s[i]], f[j] + s[i] * s[i]);
            chkmin(f[j + i * d[i]], f[j] + 2ll * d[i] * j + 1ll * d[i] * d[i] * i);
            f[j] = INF;
        }
    }
    ll ans = INF;
    FOR(j, 0, n * mx) if (f[j] < INF) chkmin(ans, f[j] * n - 1ll * j * j);
    printf("%lld\n", ans);
    return (0 ^ 0);
}