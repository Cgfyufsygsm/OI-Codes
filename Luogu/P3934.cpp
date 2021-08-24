#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
const int maxc = 1 << 23;
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
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

typedef long long ll;
const int maxn = 500000 + 5;
const int maxp = 2e7 + 5;

int p[maxp], phi[maxp], vis[maxp], cntp;

void init(int N = 20000000) {
    phi[1] = 1;
    FOR(i, 2, N) {
        if (!vis[i]) p[++cntp] = i, phi[i] = i - 1;
        for (int j = 1; j <= cntp && 1ll * i * p[j] <= N; ++j) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
    return;
}

int n, m, a[maxn];

ll tree[maxn];

il int lowbit(int x) {return x & -x;}

void add(int x, ll val) {
    for (; x <= n; x += lowbit(x))
        tree[x] += val;
    return;
}

ll query(int x) {
    ll ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree[x];
    return ret;
}

int mod[maxn];

int qPow(ll base, int p, int mod, bool &flag) {
    flag = 0;
    ll res = 1;
    if (base >= mod) flag = 1, base %= mod;
    for (; p; p >>= 1) {
        if (p & 1) {
            res = res * base;
            if (res >= mod) res %= mod, flag = 1;
        }
        base = base * base;
        if (base >= mod) base %= mod, flag = 1;
    }
    return res;
}

int main() {
    read(n), read(m);
    init();
    FOR(i, 1, n) read(a[i]), add(i, a[i] - a[i - 1]);
    while (m--) {
        int op, l, r;
        ll p;
        read(op), read(l), read(r), read(p);
        if (op == 1) add(l, p), add(r + 1, -p);
        else {
            int now = l;
            mod[l] = p, p = phi[p];
            while (now < r && p > 1) {
                mod[++now] = p;
                p = phi[p];
            }
            bool flag;
            ll res = 1;
            DEC(i, now, l) {
                res = qPow(query(i), res, mod[i], flag);
                if (flag) res += mod[i];
            }
            print(res % mod[l]), putchar('\n');
        }
    }
    return output(), 0;
}