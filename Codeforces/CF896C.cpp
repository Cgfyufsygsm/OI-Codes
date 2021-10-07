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

using ll = long long;

ll qPow(ll base, ll exp, ll mod) {
    ll ret = 1;
    for (base %= mod; exp; exp >>= 1, base = base * base % mod)
        if (exp & 1) ret = ret * base % mod;
    return ret;
}

struct node {
    ll l, r;
    mutable ll val;
    node(ll _l = 0, ll _r = 0, ll _val = 0) : l(_l), r(_r), val(_val) {}
    il bool operator<(const node &rhs) const {return l < rhs.l;}
};

std::set<node> S;

using IT = std::set<node>::iterator;

IT split(int pos) {
    auto it = S.lower_bound(node(pos));
    if (it != S.end() && it->l == pos) return it;
    --it;
    if (it->r < pos) return S.end();
    ll l = it->l, r = it->r, val = it->val;
    S.erase(it);
    S.insert(node(l, pos - 1, val));
    return S.insert(node(pos, r, val)).first;
}

void assign(ll l, ll r, ll val) {
    auto itr = split(r + 1), itl = split(l);
    S.erase(itl, itr);
    S.insert(node(l, r, val));
    return;
}

void add(ll l, ll r, ll val) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it)
        it->val += val;
    return;
}

ll query(ll l, ll r, ll x, ll mod) {
    auto itr = split(r + 1), itl = split(l);
    ll ans = 0;
    for (auto it = itl; it != itr; ++it)
        ans = (ans + qPow(it->val, x, mod) * (it->r - it->l + 1) % mod) % mod;
    return ans;
}

struct rnk {
    ll val, cnt;
    rnk(ll _v = 0, ll _c = 0) : val(_v), cnt(_c) {}
    il bool operator<(const rnk &rhs) const {return val < rhs.val;}
};

ll kth(ll l, ll r, ll k) {
    auto itr = split(r + 1), itl = split(l);
    std::vector<rnk> vec;
    for (auto it = itl; it != itr; ++it)
        vec.push_back(rnk(it->val, it->r - it->l + 1));
    std::sort(vec.begin(), vec.end());
    for (auto r : vec) {
        if (r.cnt < k) k -= r.cnt;
        else return r.val;
    }
    return -1;
}

const ll mod7 = 1e9 + 7, mod9 = 1e9 + 9;
int n, m;
ll seed, vmax;

ll rnd() {
    ll ret = seed;
    seed = (seed * 7 + 13) % mod7;
    return ret;
}

int main() {
    read(n), read(m), read(seed), read(vmax);
    FOR(i, 1, n) S.insert(node(i, i, rnd() % vmax + 1));
    FOR(i, 1, m) {
        int op = (rnd() % 4) + 1;
        ll l = rnd() % n + 1, r = rnd() % n + 1, x;
        if (l > r) std::swap(l, r);
        if (op == 3) {
            x = (rnd() % (r - l + 1)) + 1;
            print(kth(l, r, x), '\n');
        } else x = rnd() % vmax + 1;
        if (op == 1) add(l, r, x);
        else if (op == 2) assign(l, r, x);
        else if (op == 4) {
            ll y = rnd() % vmax + 1;
            print(query(l, r, x, y), '\n');
        }
    }
    return output(), 0;
}