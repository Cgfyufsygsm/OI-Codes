#include <cstdio>
#include <cctype>
#include <cmath>
#define reg register
#define il inline
#define FOR(i, a, b) for (reg int i = a; i <= b; ++i)

il int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

il int min(int a, int b) {return a < b ? a : b;}

const int maxn = 50005;
int a[maxn], bl[maxn], tag[maxn], block;

int main()
{
    int n = read();
    block = sqrt(n);
    FOR(i, 1, n) a[i] = read(), bl[i] = (i - 1) / block + 1;
    reg int l, r, c, opt;
    while (n--)
    {
        opt = read(), l = read(), r = read(), c = read();
        if (!opt)
        {
            FOR(i, l, min(bl[l] * block, r))
                a[i] += c;
            if (bl[l] != bl[r])
                FOR(i, (bl[r] - 1) * block + 1, r)
                    a[i] += c;
            FOR(i, bl[l] + 1, bl[r] - 1)
                tag[i] += c;
        }
        else printf("%d\n", a[r] + tag[bl[r]]);
    }
    return 0;
}