#include <cstdio>
#include <cctype>
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

const int maxn = 105;
int a[maxn], dep[maxn];

void build(int i, int j, int d)
{
    if (i > j) return;
    int maxa = -1, pos;
    FOR(k, i, j)
        if (a[k] > maxa)
            maxa = a[k], pos = k;
    dep[pos] = d;
    build(i, pos - 1, d + 1);
    build(pos + 1, j, d + 1);
    return;
}

int main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        FOR(i, 1, n)
            a[i] = read(), dep[i] = 0;
        build(1, n, 0);
        FOR(i, 1, n) printf("%d ", dep[i]);
        puts("");
    }
    return 0;
}