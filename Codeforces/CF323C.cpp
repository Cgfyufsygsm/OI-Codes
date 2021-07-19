#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

il int min(int a, int b) {return a < b ? a : b;}
il int max(int a, int b) {return a > b ? a : b;}

const int maxn = 1e6 + 5, maxm = 4e7 + 5;
int n, posa[maxn], b[maxn];

struct node {
    int ls, rs, sum;
} t[maxm];

int cnt, root[maxn], last = 0;

#define ls(k) t[k].ls
#define rs(k) t[k].rs
#define M ((i + j) >> 1)

int insert(int k, int i, int j, int val) {
    t[++cnt] = t[k], k = cnt;
    if (i == j) {
        ++t[k].sum;
        return k;
    }
    if (val <= M) ls(k) = insert(ls(k), i, M, val);
    else rs(k) = insert(rs(k), M + 1, j, val);
    t[k].sum = t[ls(k)].sum + t[rs(k)].sum;
    return k;
}

int query(int k, int i, int j, int x, int y) {
    if (!k) return 0;
    if (x <= i && y >= j) return t[k].sum;
    int ret = 0;
    if (x <= M) ret += query(ls(k), i, M, x, y);
    if (y > M) ret += query(rs(k), M + 1, j, x, y);
    return ret;
}

il int f(int z) {return (z - 1 + last) % n + 1;}

int main() {
    n = read();
    FOR(i, 1, n) posa[read()] = i;
    FOR(i, 1, n) root[i] = insert(root[i - 1], 1, n, posa[read()]);
    int m = read();
    while (m--) {
        int a = read(), b = read(), c = read(), d = read();
        int l1 = min(f(a), f(b)), r1 = max(f(a), f(b)), l2 = min(f(c), f(d)), r2 = max(f(c), f(d));
        printf("%d\n", last = query(root[r2], 1, n, l1, r1) - query(root[l2 - 1], 1, n, l1, r1));
        ++last;
    }
    return 0;
}