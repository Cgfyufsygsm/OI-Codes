#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (ll i = a; i >= b; --i)

typedef long long ll;

ll read()
{
    ll s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 1e5 * 32 * 2 + 5;
int trie[maxn][2], cnt;
ll val[maxn];

void insert(ll x)
{
    int p = 0;
    DEC(i, 32, 0)
    {
        int now = ((x >> i) & 1);
        if (!trie[p][now])
            trie[p][now] = ++cnt;
        p = trie[p][now];
    }
    val[p] = x;
    return;
}

ll query(ll x)
{
    int p = 0;
    DEC(i, 32, 0)
    {
        int now = (((x >> i) & 1) ^ 1);
        if (!trie[p][now])
            p = trie[p][now ^ 1];
        else p = trie[p][now];
    }
    return val[p];
}

int main()
{
    int T = read();
    FOR(kase, 1, T)
    {
        if (kase > 1)
        {
            memset(trie, 0, sizeof trie);
            cnt = 0;
        }
        int n = read(), m = read();
        while (n--)
            insert(read());
        printf("Case #%d:\n", kase);
        while (m--)
            printf("%lld\n", query(read()));
    }
    return 0;
}