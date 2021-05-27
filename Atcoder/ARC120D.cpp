#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 4e5 + 5;

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

int n, color[maxn], stk[maxn], top;

struct node
{
    int v, i;
    bool operator<(const node &b) const {return v < b.v;}
} a[maxn];

int main()
{
    n = read() << 1;
    FOR(i, 1, n) a[i].v = read(), a[i].i = i;
    std::sort(a + 1, a + n + 1);
    FOR(i, 1, n >> 1) color[a[i].i] = 1;
    FOR(i, 1, n)
    {
        if (top && color[stk[top]] != color[i]) --top, putchar(')');
        else stk[++top] = i, putchar('(');
    }
    return 0;
}