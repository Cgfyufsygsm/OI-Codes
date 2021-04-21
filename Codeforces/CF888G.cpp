#include <cstdio>
#include <cctype>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
const int maxn = 2e5 + 5;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline ll min(ll a, ll b) {return a < b ? a : b;}

int n;

int ch[maxn * 32][2], tot;
ll ans = 0;

void insert(int x)
{
    int p = 0;
    DEC(i, 30, 0)
    {
        int tmp = (x >> i) & 1;
        if (!ch[p][tmp])
            ch[p][tmp] = ++tot, ch[tot][0] = ch[tot][1] = 0;
        p = ch[p][tmp];
    }
    return;
}

int query(int x)
{
    int p = 0, ret = 0;
    DEC(i, 30, 0)
    {
        int tmp = (x >> i) & 1;
        if (ch[p][tmp]) p = ch[p][tmp];
        else if (ch[p][tmp ^ 1]) p = ch[p][tmp ^ 1], ret += (1 << i);
        else break;
    }
    return ret;
}

ll work(std::vector<int> a, int dep)
{
    if (dep < 0 || a.empty()) return 0;
    std::vector<int> b[2];
    ll ret = 0;
    FOR(i, 0, a.size() - 1) b[(a[i] >> dep) & 1].push_back(a[i]);
    if (b[0].size() && b[1].size())
    {
        tot = ch[0][0] = ch[0][1] = 0;
        ret = 1e9;
        FOR(i, 0, b[0].size() - 1)
            insert(b[0][i]);
        FOR(i, 0, b[1].size() - 1)
            ret = min(ret, query(b[1][i]));
    }
    return ret + work(b[0], dep - 1) + work(b[1], dep - 1);
}

int main()
{
    n = read();
    std::vector<int> a;
    FOR(i, 1, n) a.push_back(read());
    printf("%lld\n", work(a, 30));
    return 0;
}