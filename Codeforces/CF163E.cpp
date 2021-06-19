#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

using namespace std;
const int maxn = 1e6 + 5;

int n, k;

struct node
{
    int ch[26], fail;
} t[maxn];

int tot, pos[maxn], cnt[maxn];

void insert(char *s, int id)
{
    int u = 0, len = strlen(s + 1);
    for (int i = 1; i <= len; ++i)
    {
        int c = s[i] - 'a';
        if (!t[u].ch[c]) t[u].ch[c] = ++tot;
        u = t[u].ch[c];
    }
    pos[id] = u;
    return;
}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void build()
{
    static int q[maxn], head = 1, tail = 0;
    FOR(c, 0, 25) if (t[0].ch[c]) q[++tail] = t[0].ch[c], add(0, t[0].ch[c]);
    while (head <= tail)
    {
        int u = q[head++];
        FOR(c, 0, 25)
            if (t[u].ch[c])
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c], add(t[t[u].ch[c]].fail, t[u].ch[c]), q[++tail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
    }
    return;
}

int dfn[maxn], low[maxn], cntdfn;

void buildFail(int u)
{
    dfn[u] = ++cntdfn;
    for (int i = head[u]; i; i = nxt[i])
        buildFail(to[i]);
    low[u] = cntdfn;
    return;
}

struct BIT
{
    int t[maxn];
    int n;
#define lowbit(x) (x & -x)
    void add(int x, int v)
    {
        for (; x <= n; x += lowbit(x))
            t[x] += v;
        return;
    }
    int query(int x)
    {
        int ret = 0;
        for (; x; x -= lowbit(x))
            ret += t[x];
        return ret;
    }
} bit;

char s[maxn];

int main()
{
    scanf("%d %d", &n, &k);
    FOR(i, 1, k) scanf("%s", s + 1), insert(s, i);
    build();
    buildFail(0);
    bit.n = cntdfn + 3;
    FOR(i, 1, k) cnt[i] = 1, bit.add(dfn[pos[i]], 1), bit.add(low[pos[i]] + 1, -1);
    FOR(i, 1, n)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        if (s[1] == '?')
        {
            int ans = 0, u = 0;
            FOR(i, 2, len)
            {
                int c = s[i] - 'a';
                u = t[u].ch[c], ans += bit.query(dfn[u]);
            }
            printf("%d\n", ans);
        }
        else
        {
            int a = 0;
            FOR(j, 2, len)
                a = 10 * a + s[j] - '0';
            if (s[1] == '+' && !cnt[a]) cnt[a] = 1, bit.add(dfn[pos[a]], 1), bit.add(low[pos[a]] + 1, -1);
            else if (s[1] == '-' && cnt[a]) cnt[a] = 0, bit.add(dfn[pos[a]], -1), bit.add(low[pos[a]] + 1, 1);
        }
    }
    return 0;        
}