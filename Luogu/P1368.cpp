#include <cstdio>
#include <cctype>

int read()
{
    int s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 3e5 + 5;

int a[maxn << 1];

int main()
{
    int n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = a[i + n] = read();
    int ans = 1;
    int i = 1, j = 2, k = 0;
    while (i <= n && j <= n && k < n)
    {
        if (a[i + k] == a[j + k]) ++k;
        else
        {
            a[i + k] > a[j + k] ? i = i + k + 1 : j = j + k + 1;
            if (i == j) ++j;
            k = 0;
        }
    }
    i = i < j ? i : j;
    for (int j = i; j < i + n; ++j) printf("%d ", a[j]);
    return 0;
}