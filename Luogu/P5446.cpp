#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e6 + 5;
int n, len[maxn], ans[maxn];
char s[maxn];

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        s[0] = '#', s[n + 1] = '&';
        for (int i = 1, r = 0, mid = 0; i <= n; ++i) {
            len[i] = 0;
            if (i <= r) len[i] = min(len[(mid << 1) - i], r - i + 1);
            while (s[i - len[i]] == s[i + len[i]]) ++len[i];
            if (i + len[i] > r) r = i + len[i] - 1, mid = i;
            ans[i] = 0;
        }
        DEC(i, n, 1) {
            if (i + len[i] - 1 == n) ans[i] = 1;
            if (ans[i + len[i] - 1] && i - len[i] + 1 == 1) ans[i] = 1;
        }
        FOR(i, 1, n) if (ans[i]) printf("%d ", i);
        puts("");
    }
}