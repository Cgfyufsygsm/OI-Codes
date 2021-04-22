#include <cstdio>
#include <cctype>
#include <cstring>

const int maxn = 3e5 + 5;
int ch[maxn][27], tot, fail[maxn], end[maxn];

struct queue
{
    int q[maxn], head, tail;
    queue() {head = 1, tail = 0;}
    int size() {return tail - head + 1;}
    int pop() {return q[head++];}
    void push(int x) {q[++tail] = x;}
} q;

void insert(char *s)
{
    int len = strlen(s), u = 0;
    for (int i = 0; i < len; ++i)
    {
        int now = s[i] - 'a';
        if (!ch[u][now])
            ch[u][now] = ++tot;
        u = ch[u][now];
    }
    end[u] = len;
    return;
}

void build()
{
    for (int i = 0; i < 26; ++i)
        if (ch[0][i]) q.push(ch[0][i]);
    while (q.size())
    {
        int now = q.pop();
        for (int i = 0; i < 26; ++i)
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

int stk[maxn], top, pos[maxn];
char s[maxn], tmp[maxn];

void query(char *s)
{
    int p = 0;
    for (int i = 0; s[i]; ++i)
    {
        //printf("now at %d, %d\n", p, end[p]);
        p = ch[p][s[i] - 'a'];
        pos[i] = p;
        stk[++top] = i;
        if (end[p])
        {
            top -= end[p];
            p = pos[stk[top]];
        }
    }
    return;
}


int main()
{
    scanf("%s", s);
    int n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", tmp);
        insert(tmp);
    }
    build();
    query(s);
    for (int i = 1; i <= top; ++i)
        putchar(s[stk[i]]);
    puts("");
    return 0;
} 