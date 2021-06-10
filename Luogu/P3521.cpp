#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 2e5 + 5, maxm = 7e6;

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

typedef long long ll;

inline ll min(ll a, ll b) {return a < b ? a : b;}

struct node
{
    int ls, rs, sum;
} t[maxm];

#define L(k) t[k].ls
#define R(k) t[k].rs
#define M ((i + j) >> 1)

int n, cntnode, root[maxn << 2], lson[maxn << 2], rson[maxn << 2], cnt;

void pushup(int k)
{
    t[k].sum = t[L(k)].sum + t[R(k)].sum;
    return;
}

void modify(int &k, int i, int j, int pos, int val)
{
    if (!k) k = ++cnt;
    if (i == j)
    {
        t[k].sum += val;
        return;
    }
    if (pos <= M) modify(L(k), i, M, pos, val);
    else modify(R(k), M + 1, j, pos, val);
    pushup(k);
    return;
}

int merge(int k1, int k2, int i, int j, ll &ret1, ll &ret2)
{
    if (!k1 || !k2) return k1 + k2;
    if (i == j)
    {
        t[k1].sum += t[k2].sum;
        return k1;
    }
    ret1 += 1ll * t[R(k1)].sum * t[L(k2)].sum;
    ret2 += 1ll * t[R(k2)].sum * t[L(k1)].sum;
    L(k1) = merge(L(k1), L(k2), i, M, ret1, ret2);
    R(k1) = merge(R(k1), R(k2), M + 1, j, ret1, ret2);
    pushup(k1);
    return k1;
}

ll solve(int u)
{
    int tmp = read();
    if (tmp)
    {
        modify(root[u], 1, n, tmp, 1);
        return 0;
    }
    ll ret = 0;
    ret += solve(lson[u] = ++cntnode), ret += solve(rson[u] = ++cntnode);
    ll ret1 = 0, ret2 = 0;
    root[u] = merge(root[lson[u]], root[rson[u]], 1, n, ret1, ret2);
    return ret + min(ret1, ret2);
}

int main()
{
    n = read();
    printf("%lld\n", solve(++cntnode));
    return 0;
}