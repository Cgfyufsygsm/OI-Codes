#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e6 + 5;

struct queue
{
    int a[maxn], head = 1, tail = 0;
    void push(int x) {a[++tail] = x;}
    int pop() {return a[head++];}
    int size() {return tail - head + 1;}
    void init() {head = 1, tail = 0;}
} q;

inline int max(int a, int b) {return a > b ? a : b;}

int ch[maxn][26], tot, end[maxn], fail[maxn], vis[maxn];

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
    end[p] = i;
    return;
}

void build()
{
    q.init();
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
        for (int j = p; j && ~end[j]; j = fail[j])
            ++vis[end[j]];
    }
    return;
}

char str[151][maxn];

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        memset(end, 0, sizeof end);
        memset(ch, 0, sizeof ch);
        memset(fail, 0, sizeof fail);
        tot = 0;
        FOR(i, 1, n)
        {
            scanf("%s", str[i]);
            insert(str[i], i);
        }
        build();
        scanf("%s", str[0]);
        query(str[0]);
        int ans = 0;
        FOR(i, 1, n)
            ans = max(ans, vis[i]);
        printf("%d\n", ans);
        FOR(i, 1, n)
        {
            if (vis[i] == ans)
                printf("%s\n", str[i]);
            vis[i] = 0;
        }
    }
    return 0;
}