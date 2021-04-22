#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

int n, k;
int ans[1005], tot;

int main()
{
    int T = read();
    while (T--)
    {
        n = read(), k = read();
        tot = 0;
        DEC(i, n, k + 1)
            ans[++tot] = i;
        DEC(i, k - 1, (k + 1) / 2)
            ans[++tot] = i;
        printf("%d\n", tot);
        FOR(i, 1, tot) printf("%d ", ans[i]);
        puts("");
    }
    return 0;
}