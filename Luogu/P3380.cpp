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

il int min(int a, int b) {return a < b ? a : b;}
il int max(int a, int b) {return a > b ? a : b;}

const int maxn = 5e4 + 5, INF = 2147483647;

struct node
{
    int ch[2], val, size, key;
} t[maxn * 100];

int a[maxn], n, m, root[maxn << 2], cnt;

#define L t[u].ch[0]
#define R t[u].ch[1]

il int newnode(int val) {
    t[++cnt].val = val, t[cnt].key = rand();
    t[cnt].ch[0] = t[cnt].ch[1] = 0;
    t[cnt].size = 1;
    return cnt;
}

il void pushup(int u) {t[u].size = t[L].size + t[R].size + 1;}

void split(int u, int k, int &x, int &y) {
    if (!u) {
        x = y = 0;
        return;
    }
    if (t[u].val <= k)
        x = u, split(R, k, R, y);
    else
        y = u, split(L, k, x, L);
    pushup(u);
    return;
}

int merge(int x, int y) {
    if (!x || !y) return x ^ y;
    if (t[x].key < t[y].key)
        return t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else return t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void insert(int &u, int val) {
    int x, y, z;
    split(u, val, x, z);
    y = newnode(val);
    u = merge(merge(x, y), z);
    return;
}

void delnode(int &u, int val) {
    int x, y, z;
    split(u, val - 1, x, y);
    split(y, val, y, z);
    y = merge(t[y].ch[0], t[y].ch[1]);
    u = merge(merge(x, y), z);
}

void outtree(int);

int getRank(int &u, int val) {
    int x, y, ret;
    split(u, val - 1, x, y);
    ret = t[x].size;
    u = merge(x, y);
    return ret;
}

int getKth(int u, int k) {
    if (t[L].size + 1 == k) return t[u].val;
    else if (k <= t[L].size) return getKth(L, k);
    else return getKth(R, k - t[L].size - 1);
}

int getPre(int &u, int val) {
    int x, y, ret;
    split(u, val - 1, x, y);
    if (!x) return -INF;
    ret = getKth(x, t[x].size);
    u = merge(x, y);
    return ret;
}

int getSuc(int &u, int val) {
    int x, y, ret;
    split(u, val, x, y);
    if (!y) return INF;
    ret = getKth(y, 1);
    u = merge(x, y);
    return ret;
}

#undef L
#undef R
#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k) {
    FOR(x, i, j) insert(root[k], a[x]);
    if (i == j) return;
    build(i, M, L);
    build(M + 1, j, R);
    return;
}

void modify(int i, int j, int k, int pos, int val) {
    delnode(root[k], a[pos]);
    insert(root[k], val);
    if (i == j) return;
    if (pos <= M) modify(i, M, L, pos, val);
    else modify(M + 1, j, R, pos, val);
    return;
}

int getRank(int i, int j, int k, int l, int r, int val) {
    int ret = 0;
    if (l <= i && r >= j)
        return getRank(root[k], val);
    if (l <= M) ret += getRank(i, M, L, l, r, val);
    if (r > M) ret += getRank(M + 1, j, R, l, r, val);
    return ret;
}

int getKth(int i, int j, int rnk) {
    int l = 0, r = 1e8, mid, ret;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (getRank(1, n, 1, i, j, mid) + 1 <= rnk)
            ret = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ret;
}

int getPre(int i, int j, int k, int l, int r, int val) {
    if (l <= i && r >= j)
        return getPre(root[k], val);
    int ret = -INF;
    if (l <= M) ret = max(ret, getPre(i, M, L, l, r, val));
    if (r > M) ret = max(ret, getPre(M + 1, j, R, l, r, val));
    return ret;
}

int getSuc(int i, int j, int k, int l, int r, int val) {
    
    if (l <= i && r >= j)
        return getSuc(root[k], val);
    int ret = INF;
    if (l <= M) ret = min(ret, getSuc(i, M, L, l, r, val));
    if (r > M) ret = min(ret, getSuc(M + 1, j, R, l, r, val));
    return ret;
}

int main() {
    srand(20041031);
    read(n), read(m);
    FOR(i, 1, n) read(a[i]);
    build(1, n, 1);
    int l, r, k, pos, op;
    FOR(i, 1, m) {
        read(op);
        if (op != 3) {
            read(l), read(r), read(k);
            if (op == 1) print(getRank(1, n, 1, l, r, k) + 1), putchar('\n');
            else if (op == 2) print(getKth(l, r, k)), putchar('\n');
            else if (op == 4) print(getPre(1, n, 1, l, r, k)), putchar('\n');
            else print(getSuc(1, n, 1, l, r, k)), putchar('\n');
        } else {
            read(pos), read(k);
            modify(1, n, 1, pos, k);
            a[pos] = k;
        }
    }
    return output(), 0;
}