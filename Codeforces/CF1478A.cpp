#include <cstdio>
#include <cctype>
#include <cstring>
#define init(a) memset((a), 0, sizeof (a))
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 105;
int a[maxn], n;

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

inline int max(int a, int b) {return a > b ? a : b;}

int main()
{
    int T = read();
    while (T--)
    {
        init(a);
        n = read();
        FOR(i, 1, n)
            a[i] = read();
        int cnt = 0, ans = 1;
        FOR(i, 1, n)
            if (a[i] != a[i - 1])
                cnt = 1, ans = max(ans, cnt);
            else ans = max(ans, ++cnt);
        printf("%d\n", ans);
    }
    return 0;
}