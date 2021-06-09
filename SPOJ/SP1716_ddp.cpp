#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5, INF = 0x3f3f3f3f;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline int max(int a, int b) {return a > b ? a : b;}

template<int row, int col>
struct Matrix
{
    int ele[row][col];
    Matrix() {}
    int &operator()(int a, int b) {return ele[a][b];}
};

template<int m, int n, int p> Matrix<m, p> operator*(Matrix<m, n> m1, Matrix<n, p> m2)
{
    Matrix<m, p> ret;
    memset(ret.ele, 0xcf, sizeof ret.ele);
    FOR(i, 0, m - 1)
        FOR(k, 0, n - 1)
            FOR(j, 0, p - 1)
                ret(i, j) = max(ret(i, j), m1(i, k) + m2(k, j));
    return ret;
}

struct node
{
    int l, r;
    Matrix<3, 3> val;
} tree[maxn << 2];

int n, a[maxn];
Matrix<3, 3> ID;

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushup(int k)
{
    tree[k].val = tree[R].val * tree[L].val;
    return;
}

Matrix<3, 3> makeMat(int x)
{
    Matrix<3, 3> ret;
    ret(0, 0) = ret(0, 2) = ret(1, 0) = ret(1, 2) = x;
    ret(0, 1) = ret(2, 0) = ret(2, 1) = -INF;
    ret(1, 1) = ret(2, 2) = 0;
    return ret;
}

void build(int i, int j, int k)
{
    tree[k].l = i, tree[k].r = j;
    if (i == j)
    {
        tree[k].val = makeMat(a[i] = read());
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    pushup(k);
    return;
}

Matrix<3, 3> query(int k, int x, int y)
{
    if (x > y) return ID;
    int i = tree[k].l, j = tree[k].r;
    if (x <= i && y >= j) return tree[k].val;
    Matrix<3, 3> ret = ID;
    if (x <= M) ret = query(L, x, y);
    if (y > M) ret = query(R, x, y) * ret;
    return ret;
}

void modify(int k, int x, int z)
{
    int i = tree[k].l, j = tree[k].r;
    if (i == j)
    {
        tree[k].val = makeMat(a[i] = z);
        return;
    }
    if (x <= M) modify(L, x, z);
    else modify(R, x, z);
    pushup(k);
    return;
}

int main()
{
    ID(0, 1) = ID(0, 2) = ID(1, 0) = ID(1, 2) = ID(2, 0) = ID(2, 1) = -INF;
    n = read();
    build(1, n, 1);
    int q = read();
    while (q--)
    {
        int op = read(), x = read(), y = read();
        if (!op) modify(1, x, y);
        else
        {
            Matrix<3, 1> ret;
            ret(0, 0) = ret(1, 0) = a[x], ret(2, 0) = 0;
            ret = query(1, x + 1, y) * ret;
            printf("%d\n", ret(1, 0));
        }
    }
    return 0;
}