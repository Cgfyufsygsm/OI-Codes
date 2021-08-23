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
} // namespace fastIO

using namespace fastIO;

typedef long long ll;

struct Bigint {
    static const ll base = 1e15;
    ll upper, lower;
    Bigint(ll u, ll l) : upper(u), lower(l) {}
    il friend Bigint operator+(const Bigint &lhs, const Bigint &rhs) {
        return Bigint(lhs.upper + rhs.upper + (lhs.lower + rhs.lower) / base, (lhs.lower + rhs.lower) % base);
    }
    il friend Bigint operator*(const Bigint &lhs, const ll &rhs) {
        return Bigint(lhs.upper * rhs + lhs.lower * rhs / base, lhs.lower * rhs % base);
    }
    il friend Bigint operator/(const Bigint &lhs, const ll &rhs) {
        return Bigint(lhs.upper / rhs, (lhs.lower + lhs.upper % rhs * base) / rhs);
    }
    il friend ll operator%(const Bigint &lhs, const ll &rhs) {
        return (lhs.upper % rhs * base + lhs.lower) % rhs;
    }
    il void print() {
        if (upper) printf("%lld%015lld", upper, lower);
        else printf("%lld", lower);
    }
};


const int maxn = 1e5 + 5, maxm = 5 * maxn;
const int prime[] = {2, 3, 5};
int head[maxn], to[maxm], nxt[maxm], n, m, cnte;
int oud[maxn], ind[maxn];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

struct Frac {
    Bigint upper, lower;
    Frac(Bigint x = Bigint(0, 0), Bigint y = Bigint(0, 1)) : upper(x), lower(y) {}
    il friend Frac operator+(const Frac &lhs, const Frac &rhs) {
        return Frac(lhs.upper + rhs.upper, lhs.lower);
    }
    il friend Frac operator/(const Frac &lhs, const ll &rhs) {
        return Frac(lhs.upper / rhs, lhs.lower);
    }
} f[maxn];

int q[maxn], qhead = 1, qtail = 0;

int main() {
    Bigint base(0, 1);
    FOR(i, 1, 11) base = base * 60;
    read(n), read(m);
    FOR(i, 1, n) {
        read(oud[i]);
        FOR(j, 1, oud[i]) {
            int to; read(to);
            add(i, to), ++ind[to];
        }
        f[i] = Frac(Bigint(0, 0), base);
    }
    FOR(i, 1, m)
        q[++qtail] = i, f[i].upper = base;
    while (qhead <= qtail) {
        int u = q[qhead++];
        Frac add;
        if (oud[u]) add = f[u] / oud[u];
        for (int i = head[u]; i; i = nxt[i]) {
            int &v = to[i];
            f[v] = f[v] + add;
            if (!--ind[v])
                q[++qtail] = v;
        }
    }
    FOR(i, 1, n) {
        if (!oud[i]) {
            FOR(j, 0, 2)
                while (f[i].upper % prime[j] == 0 && f[i].lower % prime[j] == 0)
                    f[i].upper = f[i].upper / prime[j], f[i].lower = f[i].lower / prime[j];
            f[i].upper.print(), putchar(' '), f[i].lower.print(), putchar('\n');
        }
    }
    return 0;
}