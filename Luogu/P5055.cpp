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
    char obuf[maxc], *__pO = obuf;
    il void putchar(char c) {*__pO++ = c;}
    template<typename T> void print(T x) {
        if (x < T(0)) putchar('-'), print(-x);
        else {
            if (x > 9) print(x / 10);
            putchar(x % 10 + '0');
        }
        return;
    }
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

template<typename T> il void swap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

typedef long long ll;
const int maxn = 2e5 + 5;
int root[maxn], cnt;

struct node
{
    int ch[2], val, size, key;
    ll sum;
    bool rev;
} t[maxn * 100];

#define L t[u].ch[0]
#define R t[u].ch[1]

il int newnode(int val) {
    t[++cnt].size = 1, t[cnt].key = rand();
    t[cnt].val = t[cnt].sum = val;
    return cnt;
}

int clone(int u) {
    t[++cnt] = t[u];
    return cnt;
}

il void pushdown(int u) {
    if (t[u].rev) {
        if (L) L = clone(L), t[L].rev ^= 1;
        if (R) R = clone(R), t[R].rev ^= 1;
        swap(L, R), t[u].rev = 0;
    }
    return;
}

il void pushup(int u) {
    t[u].size = t[L].size + t[R].size + 1;
    t[u].sum = t[L].sum + t[u].val + t[R].sum;
    return;
}

void split(int u, int sz, int &x, int &y) {
    if (!u) {
        x = y = 0;
        return;
    }
    pushdown(u);
    if (t[L].size + 1 <= sz)
        x = clone(u), split(t[x].ch[1], sz - t[L].size - 1, t[x].ch[1], y), pushup(x);
    else y = clone(u), split(t[y].ch[0], sz, x, t[y].ch[0]), pushup(y);
    return;
}

int merge(int x, int y) {
    if (!x || !y) return x ^ y;
    if (t[x].key < t[y].key)
        return pushdown(x), t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else return pushdown(y), t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void insert(int &root, int pos, int val) {
    int x, y;
    split(root, pos, x, y);
    root = merge(merge(x, newnode(val)), y);
    return;
}

void delnode(int &root, int pos) {
    int x, y, z;
    split(root, pos - 1, x, y);
    split(y, 1, y, z);
    root = merge(x, z);
    return;
}

void reverse(int &root, int l, int r) {
    int x, y, z;
    split(root, r, x, z);
    split(x, l - 1, x, y);
    t[y].rev ^= 1;
    root = merge(merge(x, y), z);
    return;
}

ll getSum(int root, int l, int r) {
    int x, y, z;
    split(root, r, x, z);
    split(x, l - 1, x, y);
    ll ret = t[y].sum;
    root = merge(merge(x, y), z);
    return ret;
}

int main() {
    srand(20041031);
    ll last = 0;
    int n; read(n);
    FOR(i, 1, n) {
        int v, op, p, x, l, r;
        read(v), read(op);
        root[i] = root[v];
        if (op == 1) {
            read(p), read(x), p ^= last, x ^= last;
            insert(root[i], p, x);
        } else if (op == 2) {
            read(p), p ^= last;
            delnode(root[i], p);
        } else if (op == 3) {
            read(l), read(r), l ^= last, r ^= last;
            reverse(root[i], l, r);
        } else {
            read(l), read(r), l ^= last, r ^= last;
            print(last = getSum(root[i], l, r)), putchar('\n');
        }
    }
    return output(), 0;
}