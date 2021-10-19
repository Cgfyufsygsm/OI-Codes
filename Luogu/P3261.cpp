#include <bits/stdc++.h>
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
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;
using namespace std;

const int maxn = 3e5 + 5;
using ll = long long;
using ldb = long double;
int n, m, a[maxn], dead[maxn], st[maxn], ed[maxn], dep[maxn], rt[maxn];
ll h[maxn], v[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add_edge(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

il ll gcd(const ll &a, const ll &b) {return !b ? a : gcd(b, a % b);}

struct Num {
    int id;
    ll num, div;
    Num(int i = 0, ll n = 0, ll d = 1) : id(i), num(n), div(d) {}
    il void check() {ll g = gcd(num, div); num /= g, div /= g; return;}
    friend il Num operator+(Num a, ll b) {a.num += a.div * b; a.check(); return a;}
    friend il Num operator*(Num a, ll b) {ll g = gcd(a.div, b); a.div /= g, b /= g, a.num *= b; return a;}
    friend il Num operator/(Num a, ll b) {ll g = gcd(a.num, b); a.num /= g, b /= g, a.div *= b; return a;}
    friend il bool operator<(Num a, Num b) {return (ldb)a.num / a.div > (ldb)b.num / b.div;}
};

priority_queue<Num> pq[maxn];
ll add[maxn], mul[maxn];
int merge(int u, int v) {
    if (pq[u].size() < pq[v].size()) swap(u, v);
    while (!pq[v].empty()) {
        auto now = pq[v].top(); pq[v].pop();
        pq[u].push((now * mul[v] + add[v] + (-add[u])) / mul[u]);
    }
    return u;
}

void dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        dep[v] = dep[u] + 1;
        dfs(v);
        rt[u] = merge(rt[u], rt[v]);
    }
    while (!pq[rt[u]].empty()) {
        auto now = pq[rt[u]].top();
        now = now * mul[rt[u]] + add[rt[u]];
        if ((ldb)now.num / now.div < (ldb)h[u])
            ed[now.id] = u, pq[rt[u]].pop();
        else break;
    }
    if (a[u]) add[rt[u]] *= v[u], mul[rt[u]] *= v[u];
    else add[rt[u]] += v[u];
    return;
}

int main() {
    read(n), read(m);
    FOR(i, 1, n) rt[i] = i, mul[i] = 1, read(h[i]);
    FOR(i, 2, n) {
        int fa;
        read(fa), read(a[i]), read(v[i]);
        add_edge(fa, i);
    }
    FOR(i, 1, m) {
        ll s;
        read(s), read(st[i]);
        pq[st[i]].push(Num(i, (ldb)s, 1));
    }
    dep[1] = 1;
    dfs(1);
    FOR(i, 1, m) ++dead[ed[i]];
    FOR(i, 1, n) print(dead[i], '\n');
    FOR(i, 1, m) print(dep[st[i]] - dep[ed[i]], '\n');
    return output(), 0;
}