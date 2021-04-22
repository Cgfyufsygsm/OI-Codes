#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int maxn = 1e5 + 5;
int a[maxn], n, k;

int rndup(int a, int b)
{
    int ret = a + b;
    if (ret & 1)
        ret = (ret >> 1) + 1;
    else ret >>= 1;
    return ret;
}

int main()
{
    int T = read();
    while (T--)
    {
        n = read(), k = read();
        FOR(i, 1, n) a[i] = read();
        if (k == 0)
        {
            printf("%d\n", n);
            continue;
        }
        std::sort(a + 1, a + n + 1);
        if (a[n] == n - 1)
        {
            printf("%d\n", k + n);
            continue;
        }
        int mex = 0;
        FOR(i, 1, n)
        {
            if (a[i] == mex)
                ++mex;
            else break;
        }
        if ((*std::lower_bound(a + 1, a + n + 1, rndup(a[n], mex))) == rndup(a[n], mex))
            printf("%d\n", n);
        else printf("%d\n", n + 1);
    }
    return 0;
}