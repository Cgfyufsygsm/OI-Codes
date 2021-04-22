#include <iostream>
#define L (t[u].ch[0])
#define R (t[u].ch[1])

typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

const int maxn = 3e5 + 5;
const ll inf = 1e16;
ll n, lowest, added, delta;

struct node
{
    int ch[2], fa;
    ll val, size, cnt;
}t[maxn];

int cnt, root;

inline void maintain(int u)
{
    t[u].size = t[L].size + t[R].size + t[u].cnt;
    return;
}

inline int get(int u)
{
    return t[t[u].fa].ch[1] == u;
}

void rotate(int u)
{
    int fa = t[u].fa, gfa = t[fa].fa;
    int d1 = get(u), d2 = get(fa);
    t[fa].ch[d1] = t[u].ch[d1 ^ 1], t[t[u].ch[d1 ^ 1]].fa = fa;
    if (gfa)
        t[gfa].ch[d2] = u;
    t[u].fa = gfa;
    t[fa].fa = u, t[u].ch[d1 ^ 1] = fa;
    maintain(fa);
    maintain(u);
}

void splay(int u, int goal)
{
    while (t[u].fa != goal)
    {
        int fa = t[u].fa, gfa = t[fa].fa;
        int d1 = get(u), d2 = get(fa);
        if (gfa != goal)
        {
            if (d1 == d2)
                rotate(fa);
            else
                rotate(u);
        }
        rotate(u);
    }
    if (goal == 0)
        root = u;
}

void insert(ll val)
{
    int u = root, fa = 0;
    while (u && t[u].val != val)
        fa = u, u = t[u].ch[val > t[u].val];
    if (!u)
    {
        u = ++cnt;
        t[u].fa = fa;
        t[fa].ch[val > t[fa].val] = u;
        t[u].val = val;
        t[u].size = t[u].cnt = 1;
    }
    else if (t[u].val == val)
        t[u].cnt++;
    splay(u, 0);
    return;
}

int find(ll val)
{
    int u = root;
    while (t[u].val != val && t[u].ch[val > t[u].val])
        u = t[u].ch[val > t[u].val];
    return u;
}

void remove(ll val)
{
    splay(find(val), 0);
    if (t[root].cnt > 1)
    {
        t[root].cnt--;
        t[root].size--;
        return;
    }
    if ((!t[root].ch[0]) || (!t[root].ch[1]))
    {
        root = t[root].ch[0] + t[root].ch[1];
        t[root].fa = 0;
        return;
    }
    else
    {
        int lmax = t[root].ch[0];
        while (t[lmax].ch[1])
            lmax = t[lmax].ch[1];
        splay(lmax, root);
        t[t[root].ch[1]].fa = lmax;
        t[lmax].ch[1] = t[root].ch[1];
        t[lmax].fa = 0;
        maintain(root = lmax);
    }
    return;
}

ll kth(int k)
{
    if (t[root].size - 2 < k++)
        return -1;
    int u = root;
    while (true)
    {
        if (R && k <= t[R].size)
            u = R;
        else if (k > t[R].size + t[u].cnt)
            k -= t[R].size + t[u].cnt, u = L;
        else return t[u].val + delta;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    insert(-inf); insert(inf);
    cin >> n >> lowest;
    char x;
    ll k;
    while (n--)
    {
        cin >> x >> k;
        if (x == 'I' && k >= lowest)
            insert(k - delta), added++;
        if (x == 'A')
            delta += k;
        if (x == 'S')
        {
            delta -= k;
            insert(lowest - delta);
            int a = find(-inf), b = find(lowest - delta);
            splay(a, 0);
            splay(b, root);
            t[t[root].ch[1]].ch[0] = 0;
            maintain(t[root].ch[1]);
            remove(lowest - delta);
        }
        if (x == 'F')
            cout << kth(k) << endl;
    }
    cout << added - t[root].size + 2 << endl;
    return 0;
}