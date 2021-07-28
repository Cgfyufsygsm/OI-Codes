#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

const int maxn = 1e5 + 5, maxm = 23;
int n, m;
ll a[maxm][maxm], f[1 << maxm];
char s[maxn];

template<typename T> il void to_min(T &a, T b) {
    b < a ? a = b : 0;
    return;
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s + 1);
    FOR(i, 1, n - 1) ++a[s[i] - 'a'][s[i + 1] - 'a'], ++a[s[i + 1] - 'a'][s[i] - 'a'];
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    FOR(S, 0, (1 << m) - 1) {
        ll cnt = 0;
        FOR(j, 0, m - 1) cnt += (S >> j) & 1;
        FOR(i, 0, m - 1) {
            if ((1 << i) & S) continue;
            ll sum = 0;
            FOR(j, 0, m - 1) {
                if (j == i) continue;
                if ((1 << j) & S) sum += cnt * a[j][i];
                else sum -= cnt * a[i][j];
            }
            to_min(f[S | (1 << i)], f[S] + sum);
        }
    }
    printf("%lld\n", f[(1 << m) - 1]);
    return 0;
}