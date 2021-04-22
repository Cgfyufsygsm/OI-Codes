#include <cstdio>
#include <cctype>

const int maxx = 2e9 + 5, maxn = 1e5 + 5;

int sqr[maxn], tot;

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

int solve(int n)
{
    int l = 0, r = tot, mid;
    int ans;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (sqr[mid] <= n)
            ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

int main()
{
    for (int i = 3; i * i <= maxx; i += 2)
        sqr[++tot] = i * i;
    int T = read();
    while (T--)
    {
        int n = read();
        printf("%d\n", solve(2 * n - 1));
    }
    return 0;
}