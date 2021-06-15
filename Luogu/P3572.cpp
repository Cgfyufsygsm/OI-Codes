#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e6 + 5;

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

int n, d[maxn], k;

int work()
{
    static int q[maxn], head, tail;
    static int f[maxn];
    head = 1, tail = 1;
    q[1] = 1, f[1] = 0;
    FOR(i, 2, n)
    {
        while (head <= tail && i - q[head] > k) ++head;
        f[i] = f[q[head]] + (d[i] >= d[q[head]]);
        while (head <= tail && (f[q[tail]] > f[i] || (f[q[tail]] == f[i] && d[q[tail]] <= d[i]))) --tail;
        q[++tail] = i;
    }
    return f[n];
}

int main()
{
    n = read();
    FOR(i, 1, n) d[i] = read();
    int q = read();
    while (q--)
    {
        k = read();
        printf("%d\n", work());
    }
    return 0;
}