#include <cstdio>
#include <cctype>
#include <cstdlib>
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
    void readStr(char *s) {
        char c = getchar();
        while (!isalpha(c) && c != '-') c = getchar();
        for (int i = 0; isalpha(c) || c == '-'; ++i) s[i] = c, c = getchar();
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
}

using namespace fastIO;

il int max(int a, int b) {return a > b ? a : b;}
template<typename T> il void swap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 8e5 + 5;

struct node
{
    int ch[2], size, val, key;
    int sum, maxs, maxl, maxr;
    bool rev, same;
} t[maxn];

int cnt, root, stk[maxn], top, a[maxn];

#define L t[u].ch[0]
#define R t[u].ch[1]

int newnode(int val) {
    int u;
    if (top) {
        u = stk[top--];
        if (L) stk[++top] = L;
        if (R) stk[++top] = R;
    }
    else u = ++cnt;
    t[u].size = 1, t[u].key = rand();
    t[u].val = t[u].sum = t[u].maxs = val;
    t[u].maxl = t[u].maxr = max(0, val);
    t[u].ch[0] = t[u].ch[1] = 0;
    t[u].rev = t[u].same = 0;
    return u;
}

void reverse(int u) {
    if (!u) return;
    t[u].rev ^= 1;
    swap(t[u].maxl, t[u].maxr);
    swap(L, R);
    return;
}

void modify(int u, int c) {
    if (!u) return;
    t[u].val = c;
    t[u].sum = c * t[u].size;
    t[u].maxl = t[u].maxr = max(0, t[u].sum);
    t[u].maxs = max(t[u].sum, c);
    t[u].same = 1;
    return;
}

void pushdown(int u) {
    if (!u) return;
    if (t[u].rev) {
        reverse(L), reverse(R);
        t[u].rev = 0;
    }
    if (t[u].same) {
        modify(L, t[u].val), modify(R, t[u].val);
        t[u].same = 0;
    }
    return;
}

void pushup(int u) {
    t[u].size = t[L].size + t[R].size + 1;
    t[u].sum = t[L].sum + t[R].sum + t[u].val;
    t[u].maxl = max(max(t[L].maxl, t[L].sum + t[u].val + t[R].maxl), 0);
    t[u].maxr = max(max(t[R].maxr, t[L].maxr + t[u].val + t[R].sum), 0);
    t[u].maxs = max(t[u].val, t[u].val + t[L].maxr + t[R].maxl);
    if (L) t[u].maxs = max(t[u].maxs, t[L].maxs);
    if (R) t[u].maxs = max(t[u].maxs, t[R].maxs);
    return;
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (t[x].key < t[y].key)
        return pushdown(x), t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else return pushdown(y), t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void split(int u, int size, int &x, int &y) {
    if (!u) x = y = 0;
    else {
        pushdown(u);
        if (t[L].size < size)
            x = u, split(R, size - t[L].size - 1, R, y);
        else
            y = u, split(L, size, x, L);
        pushup(u);
    }
    return;
}

int build(int l, int r) {
    if (l == r)
        return newnode(a[l]);
    int m = (l + r) >> 1;
    return merge(build(l, m), build(m + 1, r));
}

int main() {
    int n, m;
    srand(20041031);
    read(n), read(m);
    FOR(i, 1, n) read(a[i]);
    root = build(1, n);
    char op[15];
    while (m--) {
        readStr(op);
        if (op[0] == 'I') {
            int posi, tot; read(posi), read(tot);
            FOR(i, 1, tot) read(a[i]);
            int x, y;
            split(root, posi, x, y);
            root = merge(merge(x, build(1, tot)), y);
        } else if (op[0] == 'D' || (op[0] == 'M' && op[2] == 'K') || op[0] == 'R' || op[0] == 'G') {
            int posi, tot, c; read(posi), read(tot);
            if (op[0] == 'M') read(c);
            int x, y, z;
            split(root, posi - 1, x, y);
            split(y, tot, y, z);
            if (op[0] == 'D') root = merge(x, z), stk[++top] = y;
            else {
                if (op[0] == 'M') modify(y, c);
                else if (op[0] == 'R') reverse(y);
                else if (op[0] == 'G') print(t[y].sum), putchar('\n');
                root = merge(merge(x, y), z);
            }
        } else if (op[0] == 'M' && op[2] == 'X') print(t[root].maxs), putchar('\n');
    }
    return output(), 0;
}