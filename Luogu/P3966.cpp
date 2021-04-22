#include <cstdio>
#include <cctype>
#include <cstring>

const int maxn = 3e6 + 5;
int ch[maxn][27], tot, fail[maxn];
int match[maxn];

struct queue
{
    int q[maxn], head, tail;
    queue() {head = 1, tail = 0;}
    int size() {return tail - head + 1;}
    int pop() {return q[head++];}
    void push(int x) {q[++tail] = x;}
} q;

void insert(char *s, int id)
{
    int u = 0;
    for (int i = 0; s[i]; ++i)
    {
        int now = s[i] - 'a';
        if (!ch[u][now])
            ch[u][now] = ++tot;
        u = ch[u][now];
    }
    match[id] = u;
    return;
}

void build()
{
    for (int i = 0; i <= 26; ++i)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (q.size())
    {
        int now = q.pop();
        for (int i = 0; i <= 26; ++i)
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

int head[maxn], to[maxn], nxt[maxn], size[maxn], cnt;

void query(char *s)
{
    int u = 0;
    for (int i = 0; s[i]; ++i)
    {
        u = ch[u][s[i] - 'a'];
        ++size[u];
    }
    return;
}

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        size[u] += size[v];
    }
    return;
}

char s[maxn], tmp[maxn];
int n;

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
    {
        scanf("%s", tmp);
        for (int i = 0; tmp[i]; ++i)
            s[++n] = tmp[i];
        s[++n] = 'a' + 26;
        insert(tmp, i);
    }
    //printf("%s", s + 1);
    build();
    query(s + 1);
    for (int i = 1; i <= n; ++i)
        add(fail[i], i);
    dfs(0, -1);
    for (int i = 1; i <= N; ++i)
        printf("%d\n", size[match[i]]);
    return 0;
}