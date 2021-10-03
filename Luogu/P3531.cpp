#include <cstdio>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define lowbit(x) (x & -x)

const int maxn = 1e6 + 5;
typedef long long ll;
char s1[maxn], s2[maxn];
int n, q[26][maxn], head[26], tail[26];
ll t[maxn];

ll query(int x) {
    if (!x) return 0;
    ll ret = 0;
    for (; x; x -= lowbit(x)) ret += t[x];
    return ret;
}

void add(int x) {
    if (!x) return;
    for (; x <= n; x += lowbit(x)) ++t[x];
    return;
}

int main() {
    scanf("%d", &n);
    scanf("%s\n%s", s1 + 1, s2 + 1);
    FOR(i, 0, 25) head[i] = 1, tail[i] = 0;
    FOR(i, 1, n) q[s2[i] - 'A'][++tail[s2[i] - 'A']] = i;
    ll ans = 0;
    FOR(i, 1, n) {
        int now = q[s1[i] - 'A'][head[s1[i] - 'A']++];
        ans += query(n) - query(now);
        add(now);
    }
    printf("%lld\n", ans);
    return 0;
}