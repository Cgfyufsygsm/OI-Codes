#include <cstdio>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

int main() {
    int T; scanf("%d", &T);
    FOR(kase, 1, T) {
        int n; scanf("%d", &n);
        printf("Case #%d: %d\n", kase, n >> 1);
        FOR(i, 1, n >> 1) {
            int now = i, sgn = 1;
            FOR(j, 1, n - 1) {
                int nxt = (now + sgn * j - 1 + n) % n + 1;
                printf("%d %d\n", now, nxt);
                sgn = -sgn, now = nxt;
            }
        }
    }
    return 0;
}