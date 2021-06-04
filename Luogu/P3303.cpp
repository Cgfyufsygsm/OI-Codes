#include <cstdio>
#include <queue>
#include <algorithm>
#include <unordered_map>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

const int maxl = 15, mod = 1e9 + 7;

ll n, k;

std::unordered_map<ll, int> mp;
ll cnt, h[20005], c[20005];

void init(ll x, ll cur)
{
    static const ll d[4] = {2, 3, 5 ,7};
    if (cur > n) return;
    mp[cur] = ++cnt;
    h[cnt] = cur;
    FOR(i, x, 3) init(i, cur * d[i]);
    return;
}

int num[maxl], len;
ll f[maxl][20005][2];

struct node
{
    int x, p;
    node(int _x = 0, int _p = 0) {x = _x, p = _p;}
    inline bool operator<(const node &b) const
    {
        return c[x] * c[p] < c[b.x] * c[b.p];
    }
};

std::priority_queue<node> q;

int main()
{
    scanf("%lld %lld", &n, &k);
    init(0, 1);
    ll tmp = n;
    while (tmp) num[++len] = tmp % 10, tmp /= 10;
    
    FOR(i, 1, 9)
        f[1][mp[i]][i > num[1]]++;
    FOR(i, 2, len)
        FOR(j, 1, cnt)
            FOR(k, 1, 9)
            {
                ll q = h[j];
                if (q % k) continue;
                int h = mp[q / k];
                if (k < num[i]) f[i][j][0] += f[i - 1][h][0] + f[i - 1][h][1];
                else if (k > num[i]) f[i][j][1] += f[i - 1][h][0] + f[i - 1][h][1];
                else f[i][j][1] += f[i - 1][h][1], f[i][j][0] += f[i - 1][h][0];
            }
    FOR(j, 1, cnt)
        FOR(i, 1, len)
            c[j] += f[i][j][0] + (i == len ? 0 : f[i][j][1]);
    std::sort(c + 1, c + cnt + 1);

    FOR(i, 1, cnt) q.push(node(i, cnt));
    ll ans = 0;

    k = std::min(1ll * k, 1ll * cnt * cnt);

    FOR(i, 1, k)
    {
        node u = q.top();
        q.pop();
        ans = (ans + c[u.x] * c[u.p] % mod) % mod;
        if (u.p == 1) continue;
        q.push(node(u.x, u.p - 1));
    }
    printf("%lld\n", ans);
    return 0;
}