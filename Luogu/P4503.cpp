#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef unsigned long long ll;

const int maxn = 30000 + 5, maxl = 200 + 7;
const ll p = 233;

char s[maxn][maxl];
ll hash[maxn][maxl], powp[maxl], tmp[maxn];
int n, l;

int main()
{
    scanf("%d %d %d", &n, &l, &powp[0]);
    powp[0] = 1;
    FOR(i, 1, l)
        powp[i] = powp[i - 1] * p;
    FOR(k, 1, n)
    {
        scanf("%s", &s[k][1]);
        FOR(i, 1, l)
            hash[k][i] = (hash[k][i - 1] * p + s[k][i]);
    }
    int ans = 0;
    FOR(k, 1, l)
    {
        FOR(i, 1, n)
            tmp[i] = hash[i][k - 1] * powp[l - k] + hash[i][l] - hash[i][k] * powp[l - k] ;
        std::sort(tmp + 1, tmp + n + 1);
        int sum = 1;
        FOR(i, 2, n)
            if (tmp[i] == tmp[i - 1])
                ans += (sum++);
            else sum = 1;
    }
    printf("%d\n", ans);
    return 0;
}