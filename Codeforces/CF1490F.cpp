#include <cstdio>
#include <cctype>
#include <map>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

const int maxn = 2e5 + 5;
int a[maxn], cnt[maxn], sum[maxn];
std::map<int, int> m;

int main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        m.clear();
        FOR(i, 1, n)
            ++m[read()];
        n = m.size();
        int tot = 0;
        for (auto i : m)
            cnt[++tot] = i.second;
        std::sort(cnt + 1, cnt + n + 1);
        sum[0] = 0;
        FOR(i, 1, n)
            sum[i] = sum[i - 1] + cnt[i];
        int ans = 1e9;
        sum[n + 1] = 0;
        FOR(i, 1, n)
            ans = min(ans, sum[i - 1] + sum[n] - sum[i] - (n - i) * cnt[i]);
        printf("%d\n", ans);
    }
    return 0;
}