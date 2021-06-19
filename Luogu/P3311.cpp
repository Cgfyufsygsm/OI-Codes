#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1500 + 5, mod = 1e9 + 7;

struct node
{
    int ch[10], fail, end;
} t[maxn];

int m, tot, lenn;

void insert(char *s)
{
    int u = 0, len = strlen(s + 1);
    FOR(i, 1, len)
    {
        int c = s[i] - '0';
        if (!t[u].ch[c]) t[u].ch[c] = ++tot;
        u = t[u].ch[c];
    }
    t[u].end = 1;
    return;
}

void build()
{
    static int q[maxn], head = 1, tail = 0;
    FOR(c, 0, 9)
        if (t[0].ch[c]) q[++tail] = t[0].ch[c];
    while (head <= tail)
    {
        int u = q[head++];
        FOR(c, 0, 9)
            if (t[u].ch[c])
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c], q[++tail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
        t[u].end |= t[t[u].fail].end;
    }
    return;
}

char n[maxn], s[maxn];
int f[maxn][maxn][2][2];

int dfs(int len, int pos, bool lim, bool zero)
{
    if (len <= 0) return !t[pos].end;
    if (t[pos].end) return 0;
    if (~f[len][pos][lim][zero]) return f[len][pos][lim][zero];
    int ret = 0;
    FOR(i, 0, 9)
    {
        if (lim && i > n[len] - '0') break;
        ret = (ret + dfs(len - 1, (zero && i == 0) ? 0 : t[pos].ch[i], lim && (i == n[len] - '0'), zero && i == 0)) % mod;
    }
    return f[len][pos][lim][zero] = ret;
}

int main()
{
    scanf("%s", n + 1);
    lenn = strlen(n + 1);
    scanf("%d", &m);
    FOR(i, 1, m)
    {
        scanf("%s", s + 1);
        insert(s);
    }
    build();
    std::reverse(n + 1, n + lenn + 1);
    memset(f, -1, sizeof f);
    int ans = dfs(lenn, 0, 1, 1);
    printf("%d\n", (ans -1 + mod) % mod);
    return 0;
}