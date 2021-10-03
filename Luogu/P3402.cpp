#include <cstdio>
#include <cctype>
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
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il void swap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 2e5 + 5;

int n, m, root[maxn], tot;

struct node {
    int ch[2], fa, dep;
} t[maxn * 40];

#define ls(k) t[k].ch[0]
#define rs(k) t[k].ch[1]
#define M ((i + j) >> 1)
#define fa(k) t[k].fa
#define dep(k) t[k].dep

void build(int &k, int i, int j) {
    k = ++tot;
    if (i == j) {
        fa(k) = i;
        return;
    }
    build(ls(k), i, M);
    build(rs(k), M + 1, j);
    return;
}

void update(int &k, int last, int i, int j, int x, int ff) {
    k = ++tot;
    if (i == j) {
        fa(k) = ff;
        dep(k) = dep(last);
        return;
    }
    ls(k) = ls(last), rs(k) = rs(last);
    if (x <= M) update(ls(k), ls(last), i, M, x, ff);
    else update(rs(k), rs(last), M + 1, j, x, ff);
    return;
}

void add(int k, int i, int j, int x) {
    if (i == j) {
        ++dep(k);
        return;
    }
    if (x <= M) add(ls(k), i, M, x);
    else add(rs(k), M + 1, j, x);
}

int query(int k, int i, int j, int x) {
    if (i == j) return k;
    if (x <= M) return query(ls(k), i, M, x);
    else return query(rs(k), M + 1, j, x);
}

int find(int k, int x) {
    int f = query(k, 1, n, x);
    if (fa(f) == x) return f;
    else return find(k, fa(f));
}


int main() {
    read(n), read(m);
    build(root[0], 1, n);
    FOR(i, 1, m) {
        int op; read(op);
        if (op == 2) {
            int k; read(k);
            root[i] = root[k];
        } else if (op == 1) {
            root[i] = root[i - 1];
            int a, b; read(a), read(b);
            a = find(root[i], a), b = find(root[i], b);
            if (fa(a) == fa(b)) continue;
            if (dep(a) > dep(b)) swap(a, b);
            update(root[i], root[i - 1], 1, n, fa(a), fa(b));
            if (dep(a) == dep(b)) add(root[i], 1, n, fa(b));
        } else {
            root[i] = root[i - 1];
            int a, b; read(a), read(b);
            print(fa(find(root[i], a)) == fa(find(root[i], b)) ? 1 : 0), putchar('\n');
        }
    }
    return output(), 0;
}