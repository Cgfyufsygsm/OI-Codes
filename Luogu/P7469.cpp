#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 3005;

int n;
char s[maxn], t[maxn];

int pos[maxn][26];
int last[maxn][maxn];

int head[maxn * maxn / 2], to[maxn * maxn / 2], nxt[maxn * maxn / 2], cnte, tot;
char trie[maxn * maxn / 2];

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    FOR(i, 1, n)
    {
        FOR(j, i + 1, n)
            if (!pos[i][s[j] - 'a'])
                pos[i][s[j] - 'a'] = j;
        if (!pos[0][s[i] - 'a'])
            pos[0][s[i] - 'a'] = i;
    }
    int ans = 0;
    FOR(i, 1, n)
    {
        if (!pos[0][t[i] - 'a']) continue;
        int p = 0;
        FOR(j, i, n)
        {
            if (pos[last[i][j - 1]][t[j] - 'a'])
            {
                last[i][j] = pos[last[i][j - 1]][t[j] - 'a'];
                bool flag = 0;
                for (int i = head[p]; i; i = nxt[i])
                {
                    if (trie[to[i]] == t[j])
                    {
                        flag = 1;
                        p = to[i];
                        break;
                    }
                }
                if (!flag)
                {
                    ++ans, trie[++tot] = t[j];
                    add(p, tot);
                    p = tot;
                }
            }
            else break;
        }
    }
    printf("%d\n", ans);
    return 0;
}