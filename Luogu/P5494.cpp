#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5, maxm = 7e6 + 5;

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

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

typedef long long ll;

int n, m;

struct node
{
    int ls, rs;
    ll sum;
} t[maxm];

#define L(k) t[k].ls
#define R(k) t[k].rs
#define M ((i + j) >> 1)

int root[maxn], stk[maxm], top, cnt;

il int newnode() {return top ? stk[top--] : ++cnt;}

il void delnode(int k)
{
    t[k].ls = t[k].rs = t[k].sum = 0;
    stk[++top] = k;
    return;
}

il void pushup(int k)
{
    t[k].sum = t[L(k)].sum + t[R(k)].sum;
    return;
}

void insert(int &k, int i, int j, int pos, int val)
{
    if (!k) k = newnode();
    if (i == j)
    {
        t[k].sum += val;
        return;
    }
    if (pos <= M) insert(L(k), i, M, pos, val);
    else insert(R(k), M + 1, j, pos, val);
    pushup(k);
    return;
}

void split(int k1, int &k2, ll k)
{
    if (!k1) return;
    k2 = newnode();
    ll v = t[L(k1)].sum;
    if (k > v) split(R(k1), R(k2), k - v);
    else swap(R(k1), R(k2));
    if (k < v) split(L(k1), L(k2), k);
    t[k2].sum = t[k1].sum - k;
    t[k1].sum = k;
    return;
}

ll query(int k, int i, int j, int x, int y)
{
    if (x <= i && y >= j) return t[k].sum;
    ll ret = 0;
    if (x <= M) ret += query(L(k), i, M, x, y);
    if (y > M) ret += query(R(k), M + 1, j, x, y);
    return ret;
}

int merge(int k1, int k2)
{
    if (!k1 || !k2) return k1 + k2;
    t[k1].sum += t[k2].sum;
    L(k1) = merge(L(k1), L(k2));
    R(k1) = merge(R(k1), R(k2));
    delnode(k2);
    return k1;
}

ll query(int k, int i, int j, int kth)
{
    if (i >= j) return i;
    if (t[L(k)].sum >= kth) return query(L(k), i, M, kth);
    else return query(R(k), M + 1, j, kth - t[L(k)].sum);
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n) insert(root[1], 1, n, i, read());
    int cntrt = 1;
    while (m--)
    {
        int opt = read();
        if (opt == 0)
        {
            int p = read(), x = read(), y = read();
            ll q1 = query(root[p], 1, n, 1, y), q2 = query(root[p], 1, n, x, y);
            int a = 0;
            split(root[p], root[++cntrt], q1 - q2);
            split(root[cntrt], a, q2);
            root[p] = merge(root[p], a);
        }
        else if (opt == 1)
        {
            int x = read(), y = read();
            root[x] = merge(root[x], root[y]);
        }
        else if (opt == 2)
        {
            int p = read(), x = read(), q = read();
            insert(root[p], 1, n, q, x);
        }
        else if (opt == 3)
        {
            int p = read(), x = read(), y = read();
            printf("%lld\n", query(root[p], 1, n, x, y));
        }
        else if (opt == 4)
        {
            int p = read(), k = read();
            if (t[root[p]].sum < k) printf("-1\n");
            else printf("%lld\n", query(root[p], 1, n, k));
        }
    }
    return 0;
}