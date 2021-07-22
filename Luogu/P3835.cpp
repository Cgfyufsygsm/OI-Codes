#include <cstdio>
#include <cctype>
#include <cstdlib>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1 << 21;
    char ibuf[maxc], * __p1 = ibuf, * __p2 = ibuf;
    il char getchar() { return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++; }
    template<typename T> void read(T& n) {
        int x = 0; n = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            n = n * 10 + c - '0', c = getchar();
        n = x ? -n : n;
    }
    char obuf[maxc], * __pO = obuf;
    il void putchar(char c) { *__pO++ = c; }
    template<typename T> void print(T x) {
        if (x < 0) putchar('-'), print(-x);
        else {
            if (x > 9) print(x / 10);
            putchar(x % 10 + '0');
        }
        return;
    }
    void output() { fwrite(obuf, __pO - obuf, 1, stdout); }
}

using namespace fastIO;

const int maxn = 5e5 + 5;

int root[maxn], cnt, stk[maxn], top;

struct node {
    int ch[2], size, val, key;
    void clear() {ch[0] = ch[1] = size = val = key = 0;}
} t[maxn * 50];

#define L t[u].ch[0]
#define R t[u].ch[1]

il void pushup(int u) { t[u].size = t[L].size + t[R].size + 1; }

il int newnode() { return top ? stk[top--] : ++cnt; }

il int newnode(int val) {
    int u = newnode();
    t[u].ch[0] = t[u].ch[1] = 0, t[u].size = 1, t[u].val = val, t[u].key = rand();
    return u;
}

il int clone(int u) {
    int v = newnode();
    t[v] = t[u];
    return v;
}

int merge(int x, int y) {
    if (!x || !y) return x ^ y;
    if (t[x].key < t[y].key)
        return t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else return t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void split(int u, int k, int& x, int& y) {
    if (!u) {
        x = y = 0;
        return;
    }
    if (t[u].val <= k) {
        x = clone(u);
        split(t[x].ch[1], k, t[x].ch[1], y);
        pushup(x);
    } else {
        y = clone(u);
        split(t[y].ch[0], k, x, t[y].ch[0]);
        pushup(y);
    }
    return;
}

void insert(int& u, int val) {
    int x, y, z;
    split(u, val, x, z);
    y = newnode(val);
    u = merge(merge(x, y), z);
    return;
}

void delNode(int& u, int val) {
    int x, y, z;
    split(u, val, x, z);
    split(x, val - 1, x, y);
    //stk[++top] = y, t[y].clear();
    y = merge(t[y].ch[0], t[y].ch[1]);
    u = merge(merge(x, y), z);
    return;
}

int getRank(int& u, int val) {
    int x, y;
    split(u, val - 1, x, y);
    int ans = t[x].size + 1;
    u = merge(x, y);
    return ans;
}

int getKth(int u, int k) {
    if (k == t[L].size + 1) return t[u].val;
    else if (k <= t[L].size) return getKth(L, k);
    else return getKth(R, k - t[L].size - 1);
}

int getPre(int& root, int val) {
    int x, y, ans;
    split(root, val - 1, x, y);
    if (!x) return -2147483647;
    ans = getKth(x, t[x].size);
    root = merge(x, y);
    return ans;
}

int getSuc(int& root, int val) {
    int x, y, ans;
    split(root, val, x, y);
    if (!y) return 2147483647;
    ans = getKth(y, 1);
    root = merge(x, y);
    return ans;
}

int main() {
    srand(20041031);
    int n; read(n);
    FOR(i, 1, n) {
        int v, op, val; read(v), read(op), read(val);
        root[i] = root[v];
        if (op == 1) insert(root[i], val);
        else if (op == 2) delNode(root[i], val);
        else if (op == 3) print(getRank(root[i], val)), putchar('\n');
        else if (op == 4) print(getKth(root[i], val)), putchar('\n');
        else if (op == 5) print(getPre(root[i], val)), putchar('\n');
        else if (op == 6) print(getSuc(root[i], val)), putchar('\n');
    }
    return output(), 0;
}