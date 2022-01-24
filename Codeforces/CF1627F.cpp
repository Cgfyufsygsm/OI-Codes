#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

#define mktp make_tuple

struct node {
    int x, y, w;
    node() {}
    node(int xx, int yy, int ww) : x(xx), y(yy), w(ww) {}
    il bool operator<(node rhs) const {
        return w > rhs.w;
    }
};

map<tuple<int, int, int, int>, int> mp;

const int fx[] = {1, -1, 0, 0};
const int fy[] = {0, 0, 1, -1};
bool vis[510][510];

int main() {
    int T; read(T);
    while (T--) {
        int n, k; read(n, k);
        map<tuple<int, int, int, int>, int>().swap(mp);
        FOR(i, 0, k) FOR(j, 0, k) vis[i][j] = 0;
        FOR(i, 1, n) {
            int r1, c1, r2, c2; read(r1, c1, r2, c2);
            if (r1 > r2) myswap(r1, r2);
            if (c1 > c2) myswap(c1, c2);
            if (r1 == r2) mp[mktp(r1 - 1, c1, r1, c1)]++, mp[mktp(r1, c1, r1 - 1, c1)]++;
            if (c1 == c2) mp[mktp(r1, c1 - 1, r1, c1)]++, mp[mktp(r1, c1, r1, c1 - 1)]++;
        }
        priority_queue<node> q;
        q.push(node(k >> 1, k >> 1, 0));
        while (!q.empty()) {
            auto now = q.top(); q.pop();
            if (vis[now.x][now.y]) continue;
            vis[now.x][now.y] = vis[k - now.x][k - now.y] = 1;
            if (!now.x || now.x == k || !now.y || now.y == k) {
                print(n - now.w);
                break;
            }
            FOR(d, 0, 3) {
                int tx = now.x + fx[d], ty = now.y + fy[d];
                if (tx < 0 || tx > k || ty < 0 || ty > k) continue;
                if (vis[tx][ty]) continue;
                q.push(node(tx, ty, now.w + mp[mktp(now.x, now.y, tx, ty)] + mp[mktp(k - now.x, k - now.y, k - tx, k - ty)]));
            }
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}