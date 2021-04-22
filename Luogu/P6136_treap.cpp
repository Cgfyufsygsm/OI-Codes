#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdlib>
#define L t[u].ch[0]
#define R t[u].ch[1]

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x?-s:s;
}

inline int max(int a,int b){return a > b? a : b;}
inline int min(int a,int b){return a < b? a : b;}

const int maxn = 2e6+5, inf = INT_MAX-20;
int cnt, root, lastans = 0, ans = 0;

struct treap
{
    int ch[2];
    int val, p;
    int size, cnt;
} t[maxn];

inline void maintain(int u)
{
    t[u].size = t[u].cnt + t[L].size + t[R].size;
    return;
}

inline void rotate(int &u, int d)
{
    int k = t[u].ch[d];
    t[u].ch[d] = t[k].ch[d ^ 1];
    t[k].ch[d^1] = u;
    maintain(u);
    maintain(u = k);
    return;
}

void insert(int &u, int val)
{
    if (!u)
    {
        u = ++cnt;
        t[u].size = t[u].cnt = 1;
        t[u].val = val;
        t[u].p = rand();
        return;
    }
    t[u].size++;
    if (t[u].val == val)
    {
        t[u].cnt++;
        return;
    }
    int d = val > t[u].val;
    insert(t[u].ch[d], val);
    if (t[t[u].ch[d]].p < t[u].p)
        rotate(u, d);
    return;
}

void remove(int &u,int val)
{
    if (!u)
        return;
    if (t[u].val == val)
    {
        if (t[u].cnt > 1)
        {
            t[u].cnt--;
            t[u].size--;
            return;
        }
        if ((!L) || (!R))
            u = L + R;
        else
        {
            int d = t[L].p > t[R].p;
            rotate(u, d);
            remove(u, val);
        }
    }
    else
        t[u].size--, remove(t[u].ch[val > t[u].val], val);
    return;
}

int rank(int u,int val)
{
    if (!u)
        return 1;
    if (val == t[u].val)
        return t[L].size + 1;
    if (val < t[u].val)
        return rank(L, val);
    else return rank(R, val) + t[L].size + t[u].cnt;
}

int kth(int u, int k)
{
    if (!u)
        return 0;
    int lsize = L ? t[L].size : 0;
    if (k <= lsize)
        return kth(L, k);
    else if(k <= lsize + t[u].cnt)
        return t[u].val;
    else return kth(R, k - t[u].cnt - lsize);
}

int pre(int u, int val)
{
    if (!u)
        return -inf;
    if (t[u].val >= val)
        return pre(L, val);
    else return max(t[u].val, pre(R, val));
}

int suc(int u, int val)
{
    if (!u)
        return inf;
    if (t[u].val <= val)
        return suc(R, val);
    else return min(t[u].val, suc(L, val));
}

int main()
{
    int n = read(), m = read();
    srand(20041031);
    while (n--)
        insert(root, read());
    while (m--)
    {
        int opt = read(), x = read() ^ lastans;
        switch (opt)
        {
        case 1:
            insert(root, x);
            break;
        case 2:
            remove(root, x);
            break;
        case 3:
            ans ^= (lastans = rank(root, x));
            break;
        case 4:
            ans ^= (lastans = kth(root, x));
            break;
        case 5:
            ans ^= (lastans = pre(root, x));
            break;
        case 6:
            ans ^= (lastans = suc(root, x));
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}