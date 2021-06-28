#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define il inline

typedef long long ll;

const int maxn = 505, maxs = 1 << 8;
const int p[9] = {0, 2, 3, 5, 7, 11, 13, 17, 19};
int n;
ll mod;

struct node
{
    int num, big = -1, S = 0;

    void init()
    {
        int tmp = num;
        FOR(i, 1, 8)
        {
            if (tmp % p[i]) continue;
            S |= (1 << (i - 1));
            while (tmp % p[i] == 0) tmp /= p[i];
        }
        if (tmp != 1) big = tmp;
    }

    il bool operator<(const node &b) const {return big < b.big;}
} a[maxn];

ll f[maxs][maxs], f1[maxs][maxs], f2[maxs][maxs];

il void add(ll &a, ll b)
{
    a = (a + b) % mod;
    return;
}

int main()
{
    scanf("%d %lld", &n, &mod);
    FOR(i, 2, n) a[i - 1].num = i, a[i - 1].init();
    std::sort(a + 1, a + n);
    f[0][0] = 1;
    FOR(i, 1, n - 1)
    {
        if (i == 1 || a[i].big != a[i - 1].big || a[i].big == -1)
            memcpy(f1, f, sizeof f1), memcpy(f2, f, sizeof f2);
        DEC(j, 255, 0)
        {
            int tmp = j ^ 255;
            for (int k = tmp; k; k = (k - 1) & tmp)
            {
                if (j & k) continue;
                if (!(a[i].S & j)) add(f2[j][k | a[i].S], f2[j][k]);
                if (!(a[i].S & k)) add(f1[j | a[i].S][k], f1[j][k]);
            }
            add(f1[j | a[i].S][0], f1[j][0]);
            if (!(j & a[i].S)) add(f2[j][a[i].S], f2[j][0]);
        }
        if (i == n - 1 || (a[i].big != a[i + 1].big) || a[i].big == -1)
            FOR(j, 0, 255)
            {
                int tmp = 255 ^ j;
                for (int k = tmp; k; k = (k - 1) & tmp)
                    f[j][k] = ((f1[j][k] + f2[j][k]) % mod - f[j][k] + mod) % mod;
                f[j][0] = ((f1[j][0] + f2[j][0]) % mod - f[j][0] + mod) % mod;
            }
    }
    ll ans = 0;
    FOR(j, 0, 255)
    {
        int tmp = j ^ 255;
        for (int k = tmp; k; k = (k - 1) & tmp)
            add(ans, f[j][k]);
        add(ans, f[j][0]);
    }
    printf("%lld\n", ans);
    return 0;
}