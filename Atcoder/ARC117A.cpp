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
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

int A, B;

int main()
{
    A = read(), B = read();
    int res = 0;
    FOR(i, 500 * 1001 + 1, 500 * 1001 + A) printf("%d ", i), res += i;
    FOR(i, 1, B - 1)
        printf("%d ", -i), res -= i;
    printf("%d\n", -res);
    return 0;
}