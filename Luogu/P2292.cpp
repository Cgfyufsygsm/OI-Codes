#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define il inline

struct node
{
    int ch[26], fail, end, g;
} t[205];

int n, m, tot;
int lens[25];

void insert(char s[], int id)
{
    int u = 0, len = strlen(s + 1);
    FOR(i, 1, len)
    {
        int c = s[i] - 'a';
        if (!t[u].ch[c]) t[u].ch[c] = ++tot;
        u = t[u].ch[c];
    }
    t[u].end = id;
    lens[id] = len;
    return;
}

void build()
{
    static int q[205], head = 1, tail = 0;
    FOR(c, 0, 25)
        if (t[0].ch[c]) q[++tail] = t[0].ch[c];
    while (head <= tail)
    {
        int u = q[head++];
        t[u].g = t[t[u].fail].g;
        if (t[u].end) t[u].g |= (1 << lens[t[u].end]);
        FOR(c, 0, 25)
            if (t[u].ch[c])
                t[t[u].ch[c]].fail = t[t[u].fail].ch[c], q[++tail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
    }
    return;
}

const int maxt = 2e6 + 5;
char s[maxt];
int f[maxt], g[maxt];

int query(char *s)
{
    int u = 0, ans = 0, len = strlen(s + 1);
    unsigned tmp = 1;
    memset(f, 0, sizeof f);
    FOR(i, 1, len)
    {
        u = t[u].ch[s[i] - 'a'];
        if (t[u].g & (tmp <<= 1))
            tmp |= 1, ans = i;
    }
    return ans;
}

int main()
{
    scanf("%d %d", &n, &m);
    FOR(i, 1, n)
    {
        scanf("%s", s + 1);
        insert(s, i);
    }
    build();
    while (m--)
    {
        scanf("%s", s + 1);
        printf("%d\n", query(s));
    }
    return 0;
}