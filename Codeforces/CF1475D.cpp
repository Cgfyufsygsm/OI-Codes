#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;
const int maxn = 2e5 + 5;
ll a1[maxn], a2[maxn];
int cnt1, cnt2, a[maxn], n, m;

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int min(int a, int b) {return a < b ? a : b;}

int main()
{
    int T = read();
    while (T--)
    {
        cnt1 = cnt2 = 0;
        n = read(), m = read();
        ll sum = 0;
        FOR(i, 1, n) sum += (a[i] = read());
        FOR(i, 1, n)
        {
            int opt = read();
            if (opt == 1)
                a1[++cnt1] = a[i];
            else a2[++cnt2] = a[i];
        }
        if (sum < m)
        {
            printf("-1\n");
            continue;
        }
        std::sort(a1 + 1, a1 + cnt1 + 1, std::greater<int>());
        std::sort(a2 + 1, a2 + cnt2 + 1, std::greater<int>());
        FOR(i, 1, cnt1) a1[i] += a1[i - 1];
        FOR(i, 1, cnt2) a2[i] += a2[i - 1];
        int ans = 1e9;
        FOR(i, 0, cnt1)
        {
            if (a2[cnt2] < m - a1[i]) continue;
            if (a1[i] >= m)
            {
                ans = min(ans, i);
                break;
            }
            ans = min(ans, i + 2 * (std::lower_bound(a2 + 1, a2 + cnt2 + 1, m - a1[i]) - a2));
        }
        printf("%d\n", ans);
    }
    return 0;
}