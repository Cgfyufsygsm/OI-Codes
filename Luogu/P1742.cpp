#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define szof(a) ((int) (a).size())
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fileIn(s) freopen(s, "r", stdin)
#define fileOut(s) freopen(s, "w", stdout)
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

using namespace std;

namespace YangTY {

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using db = double;
const int maxn = 1e5 + 5;
const db EPS = 1e-12;
struct Point {
    db x, y;
} o, p[maxn];
db r;
int n;
#define sqr(x) ((x) * (x))

il db dis(const Point &a, const Point &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void get(const Point &a, const Point &b, const Point &c) {
    db a1 = b.x - a.x, a2 = c.x - a.x, b1 = b.y - a.y, b2 = c.y - a.y;
    db c1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
    db c2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
    o = {
        (b2 * c1 - b1 * c2) / (b2 * a1 * 2 - b1 * a2 * 2), 
        (a2 * c1 - a1 * c2) / (a2 * b1 * 2 - a1 * b2 * 2)
    };
    r = dis(a, o);
    return;
}

void solve() {
    o = p[1], r = 0;
    FOR(i, 2, n) {
        if (dis(o, p[i]) > r + EPS) {
            o = p[i], r = 0;
            FOR(j, 1, i - 1) {
                if (dis(o, p[j]) > r + EPS) {
                    o.x = (p[i].x + p[j].x) / 2, o.y = (p[i].y + p[j].y) / 2;
                    r = dis(o, p[j]);
                    FOR(k, 1, j - 1) if (dis(o, p[k]) > r + EPS) get(p[i], p[j], p[k]);
                }
            }
        }
    }
}

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> p[i].x >> p[i].y;
    random_shuffle(p + 1, p + n + 1);
    solve();
    cout << fixed << setprecision(10) << r << endl << o.x << ' ' << o.y << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}