#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 3e4 + 5;

struct node
{
    int ch[2], end, fail;
} t[maxn];

int tot, n;

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
    FOR(c, 0, 1) if (t[0].ch[c]) q[++tail] = t[0].ch[c];
    while (head <= tail)
    {
        int u = q[head++];
        FOR(c, 0, 1)
            if (t[u].ch[c])
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c], q[++tail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
        t[u].end |= t[t[u].fail].end;
    }
    return;
}

bool vis[maxn];

bool dfs(int u)
{
    if (vis[u]) return true;
    vis[u] = 1;
    FOR(c, 0, 1)
        if (!t[t[u].ch[c]].end && dfs(t[u].ch[c]))
            return true;
    vis[u] = 0;
    return false;
}

char s[maxn];

int main()
{
    scanf("%d", &n);
    FOR(i, 1, n)
    {
        scanf("%s", s + 1);
        insert(s);
    }
    build();
    if (dfs(0)) puts("TAK");
    else puts("NIE");
    return 0;
}