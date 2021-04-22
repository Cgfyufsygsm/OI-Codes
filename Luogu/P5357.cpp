#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 2e6 + 5;

struct queue
{
    int a[maxn], head = 1, tail = 0;
    void push(int x) {a[++tail] = x;}
    int pop() {return a[head++];}
    int size() {return tail - head + 1;}
} q;

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;

void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

int ch[maxn][26], tot, fail[maxn], size[maxn];
int match[maxn];

void insert(char *s, int i)
{
    int len = strlen(s), p = 0;
    FOR(i, 0, len - 1)
    {
        int now = s[i] - 'a';
        if (!ch[p][now])
            ch[p][now] = ++tot;
        p = ch[p][now];
    }
    match[i] = p;
    return;
}

void build()
{
    FOR(i, 0, 26 - 1)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (q.size())
    {
        int now = q.pop();
        FOR(i, 0, 26 - 1)
        {
            if (ch[now][i])
            {
                fail[ch[now][i]] = ch[fail[now]][i];
                q.push(ch[now][i]);
            }
            else ch[now][i] = ch[fail[now]][i];
        }
    }
    return;
}

void query(char *s)
{
    int p = 0, len = strlen(s);
    FOR(i, 0, len - 1)
    {
        p = ch[p][s[i] - 'a'];
        ++size[p];
    }
    return;
}

char str[maxn];

void dfs(int u, int fa)
{
    //printf("now at %d\n", u);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        size[u] += size[v];
    }
    return;
}

int main()
{
    int n;
    scanf("%d", &n);
    FOR(i, 1, n)
    {
        scanf("%s", str);
        insert(str, i);
    }
    build();
    scanf("%s", str);
    query(str);
    FOR(i, 1, tot)
        add(fail[i], i);
    dfs(0, -1);
    FOR(i, 1, n) printf("%d\n", size[match[i]]);
    return 0;
}