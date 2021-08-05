#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 2e5 + 5, maxm = 8e6;

int read() {
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

int n, a[maxn], b[maxn], tot;

struct node {
    int ls, rs, sum;
} t[maxm];

int cnt, root[maxn];

#define L(k) t[k].ls
#define R(k) t[k].rs
#define M ((i + j) >> 1)

inline int clone(int k) {
    t[++cnt] = t[k];
    return cnt;
}

int insert(int k, int i, int j, int x) {
    k = clone(k);
    if (i == j)     {
        ++t[k].sum;
        return k;
    }
    if (x <= M) L(k) = insert(L(k), i, M, x);
    else R(k) = insert(R(k), M + 1, j, x);
    t[k].sum = t[L(k)].sum + t[R(k)].sum;
    return k;
}

int query(int k1, int k2, int i, int j, int k) {
    if (i >= j) return i;
    int x = t[L(k2)].sum - t[L(k1)].sum;
    if (x >= k) return query(L(k1), L(k2), i, M, k);
    else return query(R(k1), R(k2), M + 1, j, k - x);
}

int main() {
    n = read();
    int m = read();
    FOR(i, 1, n) a[i] = b[i] = read();
    std::sort(b + 1, b + n + 1);
    tot = std::unique(b + 1, b + n + 1) - b - 1;
    FOR(i, 1, n) root[i] = insert(root[i - 1], 1, tot, std::lower_bound(b + 1, b + tot + 1, a[i]) - b);
    while (m--)     {
        int l = read(), r = read(), k = read();
        printf("%d\n", b[query(root[l - 1], root[r], 1, tot, k)]);
    }
    return 0;
}