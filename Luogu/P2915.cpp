#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 18;

int n, k, s[maxn];

typedef long long ll;

ll f[1 << maxn][maxn];

int myabs(int x) {return x > 0 ? x : -x;}

int main()
{
    scanf("%d %d", &n, &k);
    FOR(i, 1, n) scanf("%d", s + i);
    FOR(i, 1 ,n) f[1 << (i - 1)][i] = 1;
    FOR(S, 1, (1 << n) - 1)
    {
        FOR(i, 1, n)
        {
            if (!((1 << (i - 1)) & S)) continue;
            int S0 = (1 << (i - 1)) ^ S;
            FOR(j, 1, n)
            {
                if (!((1 << (j - 1)) & S0)) continue;
                if (myabs(s[i] - s[j]) > k) f[S][i] += f[S0][j];
            }
        }
    }
    ll sum = 0;
    FOR(i, 1, n) sum += f[(1 << n) - 1][i];
    printf("%lld\n", sum);
    return 0;
}