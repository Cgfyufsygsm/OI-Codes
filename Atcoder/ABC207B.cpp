#include <cstdio>
#include <cctype>
#include <cmath>
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

int a, b, c, d;

int main()
{
    a = read(), b = read(), c = read(), d = read();
    if (d * c <= b) puts("-1");
    else printf("%d\n", (int)ceil(double(a) / double(c * d - b)));
    return 0;
}