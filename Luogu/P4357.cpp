#include <cstdio>
#include <cctype>
#include <queue>
#include <algorithm>
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
}

using namespace fastIO;

typedef long long ll;
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}

const int maxn = 1e5 + 5;
struct point {
    ll x, y;
} p[maxn];
int n, k;
int rt, type[maxn], ls[maxn], rs[maxn];
ll L[maxn], R[maxn], U[maxn], D[maxn];
std::priority_queue<ll, std::vector<ll>, std::greater<ll> > q;

il bool cmp1(const point &a, const point &b) {return a.x < b.x;}
il bool cmp2(const point &a, const point &b) {return a.y < b.y;}

void pushup(int k) {
    L[k] = R[k] = p[k].x;
    U[k] = D[k] = p[k].y;
    if (ls[k])
        L[k] = min(L[ls[k]], L[k]), R[k] = max(R[ls[k]], R[k]),
        D[k] = min(D[ls[k]], D[k]), U[k] = max(U[ls[k]], U[k]);
    if (rs[k])
        L[k] = min(L[rs[k]], L[k]), R[k] = max(R[rs[k]], R[k]),
        D[k] = min(D[rs[k]], D[k]), U[k] = max(U[rs[k]], U[k]);
    return;
}

int build(int l, int r) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
    FOR(i, l, r) av1 += p[i].x, av2 += p[i].y;
    av1 /= (r - l + 1), av2 /= (r - l + 1);
    FOR(i, l, r) va1 += (av1 - p[i].x) * (av1 - p[i].x), va2 += (av2 - p[i].y) * (av2 - p[i].y);
    if (va1 > va2)
        std::nth_element(p + l, p + mid, p + r + 1, cmp1), type[k] = 1;
    else std::nth_element(p + l, p + mid, p + r + 1, cmp2), type[k] = 2;
    ls[mid] = build(l, mid - 1);
    rs[mid] = build(mid + 1, r);
    pushup(mid);
    return mid;
}

il ll sq(ll n) {return n * n;}

il ll dist(const point &a, const point &b) {return sq(a.x - b.x) + sq(a.y - b.y);}
il ll dist(const point &p, const int x) {
    return max(sq(p.x - L[x]), sq(p.x - R[x])) + max(sq(p.y - U[x]), sq(p.y - D[x]));
}

void query(int l, int r, int x) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    ll t = dist(p[x], p[mid]);
    if (t > q.top()) q.pop(), q.push(t);
    ll disl = dist(p[x], mid), disr = dist(p[x], mid);
    if (disl > q.top() && disr > q.top()) {
        if (disl > disr) {
            query(l, mid - 1, x);
            if (disr > q.top()) query(mid + 1, r, x);
        } else {
            query(mid + 1, r, x);
            if (disl > q.top()) query(l, mid - 1, x);
        }
    }
    return;
}

int main() {
    read(n), read(k), k <<= 1;
    FOR(i, 1, n) read(p[i].x), read(p[i].y);
    build(1, n);
    FOR(i, 1, k) q.push(0);
    FOR(i, 1, n) query(1, n, i);
    printf("%lld\n", q.top());
    return output(), 0;
}