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
} q;

int ch[maxn][26], tot, end[maxn], fail[maxn];

void insert(char *s)
{
    int len = strlen(s), p = 0;
    FOR(i, 0, len - 1)
    {
        int now = s[i] - 'a';
        if (!ch[p][now])
            ch[p][now] = ++tot;
        p = ch[p][now];
    }
    ++end[p];
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

int query(char *s)
{
    int p = 0, res = 0, len = strlen(s);
    FOR(i, 0, len - 1)
    {
        p = ch[p][s[i] - 'a'];
        for (int j = p; j && ~end[j]; j = fail[j])
            res += end[j], end[j] = -1;
    }
    return res;
}

char str[maxn];

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", str);
        insert(str);
    }
    build();
    scanf("%s", str);
    printf("%d\n", query(str));
    return 0;
}