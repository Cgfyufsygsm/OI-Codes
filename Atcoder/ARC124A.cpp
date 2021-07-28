#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1 << 21;
    char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
    il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
    template<typename T> void read(T &n) {
        int x = 0; n = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            n = n * 10 + c - '0', c = getchar();
        n = x ? -n : n;
    }
    void readChar(char &c) {
        char x = getchar();
        while (!isalpha(x)) x = getchar();
        c = x;
        return;
    }
}

using namespace fastIO;

const int mod = 998244353, maxn = 1005;
int n, k;
int cnt[maxn], vis[maxn];

int main() {
    read(n), read(k);
    FOR(i, 1, n) cnt[i] = k;
    char tmp;
    int x;
    FOR(i, 1, k) {
        readChar(tmp), read(x);
        if (tmp == 'L') {
            if (vis[x]) return puts("0"), 0;
            vis[x] = i;
            FOR(d, 1, x - 1) --cnt[d];
        } else if (tmp == 'R') {
            if (vis[x]) return puts("0"), 0;
            vis[x] = i;
            FOR(d, x + 1, n) --cnt[d];
        }
    }
    //FOR(i, 1, n) printf("%d ", cnt[i]);puts("");
    int ans = 1;
    FOR(i, 1, n) ans = 1ll * ans * (vis[i] ? 1 : cnt[i]) % mod;
    printf("%d\n", ans);
    return 0;
}
