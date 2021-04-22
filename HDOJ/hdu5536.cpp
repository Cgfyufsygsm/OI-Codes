#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 1e5 + 5;
int trie[maxn][2], cnt[maxn], tot;
int val[maxn], a[maxn];

void insert(int x)
{
    int p = 0;
    ++cnt[p];
    DEC(i, 31, 0)
    {
        int now = ((x >> i) & 1);
        if (!trie[p][now])
            trie[p][now] = ++tot;
        p = trie[p][now];
        ++cnt[p];
    }
    val[p] = x;
    return;
}

void delnode(int x)
{
    int p = 0;
    --cnt[p];
    DEC(i, 31, 0)
    {
        int now = ((x >> i) & 1);
        p = trie[p][now];
        --cnt[p];
    }
    return;
}

int query(int x)
{
    int p = 0;
    DEC(i, 31, 0)
    {
        int now = (((x >> i) & 1) ^ 1);
        if (trie[p][now] && cnt[trie[p][now]])
            p = trie[p][now];
        else p = trie[p][now ^ 1];
    }
    return val[p] ^ x;
}

int main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        FOR(i, 1, n)
            insert(a[i] = read());
        int ans = 0;
        FOR(i, 1, n)
        {
            delnode(a[i]);
            FOR(j, i + 1, n)
            {
                delnode(a[j]);
                ans = max(ans, query(a[i] + a[j]));
                insert(a[j]);
            }
            insert(a[i]);
        }
        memset(trie, 0, sizeof trie);
        memset(cnt, 0, sizeof cnt);
        memset(val, 0, sizeof val);
        tot = 0;
        printf("%d\n", ans);
    }
    return 0;
}