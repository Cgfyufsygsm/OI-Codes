#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;
const int maxn = 2e6 + 5;
const ll mod = 1e9 + 7;

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;

int fail[maxn], n;
ll ans;
char s[maxn];

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    //printf("added %d to %d\n", u, v);
    return;
}

int stk[maxn], top, mid;

void dfs(int u, int fa)
{
    if (u)
    {
        stk[++top] = u;
        while ((stk[mid] << 1) <= u) ++mid;
        while ((stk[mid] << 1) > u) --mid;
        ans *= (ll)mid;
        ans %= mod;
    }
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
    }
    --top;
    return;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(head, 0, sizeof head);
        memset(fail, 0, sizeof fail);
        cnt = 0;
        scanf("%s", s + 1);
        n = strlen(s + 1);
        add(1, 0); add(0, 1), fail[1] = 0;
        for (int i = 2, j = 0; i <= n; ++i)
        {
            while (j && s[j + 1] != s[i])
                j = fail[j];
            if (s[j + 1] == s[i]) ++j;
            fail[i] = j;
            add(fail[i], i);
            add(i, fail[i]);
        }
        ans = 1, stk[top = mid = 1] = 0;
        dfs(0, -1);
        printf("%lld\n", ans);
    }
    return 0;
}