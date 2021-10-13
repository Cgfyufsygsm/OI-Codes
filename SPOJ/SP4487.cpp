#include <cstdio>
#include <cctype>
#include <cstdlib>
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

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 2e5 + 5;

struct node {
    int ch[2], size, key, val;
    int sum, ans, lmax, rmax;
} t[maxn];

#define L (t[u].ch[0])
#define R (t[u].ch[1])

int tot, root;

il void pushup(int u) {
    t[u].sum = t[L].sum + t[R].sum + t[u].val;
    t[u].lmax = max(t[L].lmax, t[L].sum + t[u].val + t[R].lmax);
    t[u].rmax = max(t[R].rmax, t[L].rmax + t[u].val + t[R].sum);
    t[u].ans = max(max(t[u].val, t[L].rmax + t[u].val + t[R].lmax), max(t[L].ans, t[R].ans));
    t[u].size = t[L].size + t[R].size + 1;
    return;
}

il int newnode(int val) {
    t[++tot].val = val;
    t[tot].key = rand();
    t[tot].size = 1;
    t[tot].sum = t[tot].ans = val;
    t[tot].lmax = t[tot].rmax = max(0, val);
    return tot;
}

void split(int u, int size, int &x, int &y) {
    if (!u) return x = y = 0, void();
    if (t[L].size < size)
        x = u, split(R, size - t[L].size - 1, R, y);
    else y = u, split(L, size, x, L);
    pushup(u);
    return;
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (t[x].key < t[y].key) return t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else return t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

int main() {
    int n; read(n);
    FOR(i, 1, n) {
        int x; read(x);
        root = merge(root, newnode(x));
    }
    int m; read(m);
    t[0].ans = -2e9;
    FOR(i, 1, m) {
        char op[3]; read(op);
        int x, y; read(x);
        if (op[0] == 'I') {
            read(y);
            int u, v; split(root, x - 1, u, v);
            root = merge(merge(u, newnode(y)), v);
        } else if (op[0] == 'D') {
            int u, v, w;
            split(root, x - 1, u, v), split(v, 1, v, w);
            root = merge(u, w);
        } else if (op[0] == 'R') {
            read(y);
            int u, v, w;
            split(root, x - 1, u, v), split(v, 1, v, w);
            t[v].val = y; pushup(v);
            root = merge(u, merge(v, w));
        } else if (op[0] == 'Q') {
            read(y);
            int u, v, w;
            split(root, y, v, w), split(v, x - 1, u, v);
            print(t[v].ans, '\n');
            root = merge(u, merge(v, w));
        }
    }
    return output(), 0;
}