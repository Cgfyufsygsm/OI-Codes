#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int n, m;

struct node
{
    int ch[3];
    int num, fail;
    node() {memset(ch, 0, sizeof ch);}
} t[1005];

inline int max(int a, int b) {return a > b ? a : b;}

int cnt;

void insert(char *s)
{
    int l = strlen(s + 1);
    int u = 0;
    FOR(i, 1, l)
    {
        if (!t[u].ch[s[i] - 'A'])
            t[u].ch[s[i] - 'A'] = ++cnt;
        u = t[u].ch[s[i] - 'A'];
    }
    ++t[u].num;
    return;
}

void build()
{
    static int q[1005], head = 1, tail = 0;
    FOR(i, 0, 2)
        if (t[0].ch[i]) q[++tail] = t[0].ch[i];
    while (head <= tail)
    {
        int u = q[head++];
        FOR(i, 0, 2)
        {
            if (t[u].ch[i])
            {
                t[t[u].ch[i]].fail = t[t[u].fail].ch[i];
                q[++tail] = t[u].ch[i];
            }
            else t[u].ch[i] = t[t[u].fail].ch[i];
        }
        t[u].num += t[t[u].fail].num;
    }
    return;
}

int ans = 0;

void dp()
{
    static int f[1005][505];
    memset(f, 0x80, sizeof f);
    f[0][0] = 0;
    FOR(i, 1, m)
        FOR(u, 0, cnt)
            FOR(k, 0, 2)
                f[i][t[u].ch[k]] = max(f[i - 1][u] + t[t[u].ch[k]].num, f[i][t[u].ch[k]]);
    FOR(u, 1, cnt)
        ans = max(f[m][u], ans);
    return;
}

int main()
{
    scanf("%d %d", &n, &m);
    char s[20];
    FOR(i, 1, n)
    {
        scanf("%s", s + 1);
        insert(s);
    }
    build();
    dp();
    printf("%d\n", ans);
    return 0;
}