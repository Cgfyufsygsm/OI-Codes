#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 2e5 + 5, mod = 10007;

struct node
{
    int ch[26], end, fail;
} t[maxn];
int tot;

void insert(char *s)
{
    int u = 0, len = strlen(s + 1);
    FOR(i, 1, len)
    {
        int c = s[i] - 'A';
        if (!t[u].ch[c]) t[u].ch[c] = ++tot;
        u = t[u].ch[c];
    }
    t[u].end = 1;
    return;
}

void build()
{
    static int q[maxn], head = 1, tail = 0;
    FOR(c, 0, 25) if (t[0].ch[c]) q[++tail] = t[0].ch[c];
    while (head <= tail)
    {
        int u = q[head++];
        FOR(c, 0, 25)
            if (t[u].ch[c])
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c], q[++tail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
        t[u].end |= t[t[u].fail].end;
    }
    return;
}

int f[105][maxn];

int qpow(int base, int p)
{
    int ret = 1;
    for (; p; p >>= 1, base = base * base % mod)
        if (p & 1) ret = ret * base % mod;
    return ret;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    char s[105];
    FOR(i, 1, n)
    {
        scanf("%s", s + 1);
        insert(s);
    }
    build();
    int ans = qpow(26, m);
    f[0][0] = 1;
    FOR(i, 1, m)
        FOR(u, 0, tot)
            FOR(c, 0, 25)
                if (!t[t[u].ch[c]].end)
                    f[i][t[u].ch[c]] = (f[i - 1][u] + f[i][t[u].ch[c]]) % mod;
    FOR(u, 0, tot) ans = (ans - f[m][u] + mod) % mod;
    printf("%d\n", ans);
    return 0;
}