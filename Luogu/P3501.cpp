#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e6 + 5;
char s0[maxn], s[maxn];
int n, cnt, len[maxn];

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}

int main() {
    scanf("%d %s", &n, s0 + 1);
    s[cnt = 0] = '&', s[cnt = 1] = '#';
    FOR(i, 1, n) s[++cnt] = s0[i], s[++cnt] = '#';
    long long ans = 0;
    for (int i = 1, r = 0, mid = 0; i <= cnt; ++i) {
        if (i <= r) len[i] = min(len[(mid << 1) - i], r - i + 1);
        while ((s[i - len[i]] == '#' && s[i - len[i]] == s[i + len[i]]) || s[i - len[i]] + s[i + len[i]] == '0' + '1') ++len[i];
        if (i + len[i] > r) r = i + len[i] - 1, mid = i;
        if (s[i] == '#') ans += ((len[i] - 1) >> 1);
    }
    printf("%lld\n", ans);
    return 0;
}