#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define int long long

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

inline int min(int a, int b) {return a < b ? a : b;}
inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 2e5 + 5;
int sum[maxn];

struct node
{
    int val, id;
    node(){}
    node(int v, int i) {val = v, id = i;}
} a[maxn];

bool cmp1(node a, node b)
{
    return a.val < b.val;
}

bool cmp2(node a, node b)
{
    return a.id < b.id;
}

signed main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        FOR(i, 1, n) a[i].val = read(), a[i].id = i;
        std::sort(a + 1, a + 1 + n, cmp1);
        FOR(i, 1, n) sum[i] = sum[i - 1] + a[i].val;
        int ans = 0, cnt = 0;
        DEC(i, n, 1)
        {
            ++cnt;
            if (a[i].val > sum[i - 1])
            {
                ans = a[i].val;
                break;
            }
        }
        std::sort(a + 1, a + n + 1, cmp2);
        printf("%d\n", cnt);
        FOR(i, 1, n)
            if (a[i].val >= ans)
                printf("%d ", i);
        puts("");
    }
    return 0;
}