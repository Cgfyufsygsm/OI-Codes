#include <cstdio>
#include <cctype>
#include <bitset>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 2005;
std::bitset<4000005> s;
int a[maxn], n, sum;

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

int main()
{
    n = read();
    s[0] = 1;
    FOR(i, 1, n) a[i] = read(), s |= s << a[i], sum += a[i];
    FOR(i, (sum + 1) >> 1, sum) if (s[i]) return printf("%d\n", i), 0;
    return 0;
}