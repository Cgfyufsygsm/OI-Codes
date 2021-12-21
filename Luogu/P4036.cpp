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
    while (!isspace(c)) s[p++] = c, c = getchar();
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

using uint = unsigned;
const int maxn = 1e5 + 5;
const uint base = 31;
char s0[maxn];
uint p[maxn];

struct node {
    int key, size, ch[2], val;
    uint hash;
} t[maxn];
int cnt, root;

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]

void pushup(int u) {
    t[u].size = t[ls(u)].size + t[rs(u)].size + 1;
    t[u].hash = t[ls(u)].hash + t[u].val * p[t[ls(u)].size] + t[rs(u)].hash * p[t[ls(u)].size + 1];
    return;
}

void split(int u, int sz, int &x, int &y) {
    if (!u) return x = y = 0, void();
    if (t[ls(u)].size < sz) x = u, split(rs(u), sz - t[ls(u)].size - 1, rs(u), y);
    else y = u, split(ls(u), sz, x, ls(u));
    return pushup(u), void();
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (t[x].key < t[y].key)
        return t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else return t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void insert(int pos, char c) {
    int x, y;
    split(root, pos, x, y);
    ++cnt;
    t[cnt].val = t[cnt].hash = c - 'a' + 1, t[cnt].size = 1, t[cnt].key = rand();
    root = merge(x, merge(cnt, y));
    return;
}

void modify(int pos, char c) {
    int x, y, z;
    split(root, pos - 1, x, y), split(y, 1, y, z);
    t[y].val = t[y].hash = c - 'a' + 1;
    root = merge(x, merge(y, z));
    return;
}

void build() {
    int n = strlen(s0 + 1);
    FOR(i, 1, n) insert(i - 1, s0[i]);
    return;
}

uint gethash(int l, int r) {
    int x, y, z;
    split(root, l - 1, x, y), split(y, r - l + 1, y, z);
    uint res = t[y].hash;
    root = merge(x, merge(y, z));
    return res;
}

int solve(int pos1, int pos2) {
    int l = 0, r = min(t[root].size - pos2 + 1, t[root].size - pos1 + 1) + 1, res = 0;
    while (l < r) {
        int mid = (l + r) >> 1;
        uint h1 = gethash(pos1, pos1 + mid - 1), h2 = gethash(pos2, pos2 + mid - 1);
        if (h1 == h2) res = mid, l = mid + 1;
        else r = mid;
    }
    return res;
}

int main() {
    p[0] = 1;
    FOR(i, 1, maxn - 1) p[i] = p[i - 1] * base;
    read(s0 + 1);
    build();
    int m; read(m);
    while (m--) {
        char s[2], d[2]; read(s);
        int x, y;
        if (s[0] == 'Q') {
            read(x, y);
            print(solve(x, y));
        } else if (s[0] == 'R') {
            read(x, d);
            modify(x, d[0]);
        } else if (s[0] == 'I') {
            read(x, d);
            insert(x, d[0]);
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}