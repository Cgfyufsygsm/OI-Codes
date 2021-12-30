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

const int maxn = 4e5 + 5, N = 1e5;
vector<int> p[maxn];
int root[maxn], tot;
struct node {
    int ch[2], sum;
} t[maxn * 50];

#define ls(k) t[k].ch[0]
#define rs(k) t[k].ch[1]
#define M ((i + j) >> 1)

il void pushup(int k) {
    t[k].sum = t[ls(k)].sum + t[rs(k)].sum;
}

void build(int &k, int i, int j) {
    if (!k) k = ++tot;
    if (i == j) {
        t[k].sum = 0;
        return;
    }
    build(ls(k), i, M), build(rs(k), M + 1, j);
    pushup(k);
    return;
}

void update(int &k, int i, int j, int x) {
    t[++tot] = t[k], k = tot;
    if (i == j) {
        ++t[k].sum;
        return;
    }
    if (x <= M) update(ls(k), i, M, x);
    else update(rs(k), M + 1, j, x);
    pushup(k);
    return;
}

int query(int k, int i, int j, int x, int y) {
    if (!k) return 0;
    if (x <= i && y >= j) return t[k].sum;
    int ret = 0;
    if (x <= M) ret += query(ls(k), i, M, x, y);
    if (y > M) ret += query(rs(k), M + 1, j, x, y);
    return ret;
}

int check(int x, int y, int d) {
    int l = max(0, x - d - 1), r = min(2 * N + 1, x + d);
    int down = max(1, y - d), up = min(2 * N + 1, y + d);
    int ans = query(root[r], 1, 2 * N + 1, down, up) - query(root[l], 1, 2 * N + 1, down, up);
    return ans;
}

int main() {
    int n; read(n);
    FOR(i, 1, n) {
        int x, y; read(x, y);
        p[x + y + 1].push_back(x - y + N + 1);
    }
    // x : [1, 2e5 + 1]
    // y : [1, 2e5 + 1]
    build(root[0], 1, 2 * N + 1);
    FOR(i, 1, 2 * N + 1) {
        root[i] = root[i - 1];
        for (auto y : p[i]) update(root[i], 1, 2 * N + 1, y);
    }
    int q; read(q);
    while (q--) {
        int x, y, k; read(x, y, k);
        int l = 0, r = (int)2e5 + 1, ans = 0;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(x + y + 1, x - y + N + 1, mid) >= k) ans = mid, r = mid;
            else l = mid + 1;
        }
        print(ans);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}