#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

typedef long long ll;
typedef long double ldb;

const int maxn = 1e5 + 5;

char str[maxn][35];
int n, q[maxn], head, tail, k[maxn], pre[maxn];
ll L, p, s[maxn];
ldb f[maxn];

ldb qPow(ldb base) {
    ldb ret = 1;
    for (int exp = p; exp; exp >>= 1, base *= base)
        if (exp & 1) ret *= base;
    return ret;
}

template<typename T> il T abs(T x) {return x > 0 ? x : -x;}

il ldb calc(int i, int j) {return f[i] + qPow(abs(s[j] - s[i] - L - 1));}

int bound(int x, int y) {
    int l = x, r = n + 1, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (calc(x, mid) >= calc(y, mid))
            r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %lld %lld", &n, &L, &p);
        FOR(i, 1, n) scanf("%s", str[i]), s[i] = s[i - 1] + strlen(str[i]) + 1;
        q[head = tail = 1] = 0;
        FOR(i, 1, n) {
            while (head < tail && k[head] <= i) ++head;
            f[i] = calc(q[head], i), pre[i] = q[head];
            while (head < tail && k[tail - 1] >= bound(q[tail], i)) --tail;
            k[tail] = bound(q[tail], i);
            q[++tail] = i;
        }
        if (f[n] > 1e18) puts("Too hard to arrange");
        else {
            printf("%.0Lf\n", f[n]);
            q[tail = 0] = n;
            for (int i = n; i; q[++tail] = i = pre[i]);
            for (; tail; --tail) {
                FOR(i, q[tail] + 1, q[tail - 1] - 1)
                    printf("%s ", str[i]);
                puts(str[q[tail - 1]]);
            }
        }
        puts("--------------------");
    }
    return 0;
}