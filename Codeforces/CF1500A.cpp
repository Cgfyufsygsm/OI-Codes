#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 2e5 + 5, maxs = 5e6 + 5;

struct node
{
    int id, val;
    bool operator<(const node &b) const
    {
        if (val == b.val) return id < b.id;
        else return val < b.val;
    }
} a[maxn], ans[maxs];

int n;

int main()
{
    n = read();
    FOR(i, 1, n) a[i].val = read(), a[i].id = i;
    std::sort(a + 1, a + n + 1);
    int cnt = 0;
    FOR(i, 1, n)
        FOR(j, i + 1, n)
        {
            int s = a[i].val + a[j].val;
            if (ans[s].id + ans[s].val && ans[s].id != a[i].id && ans[s].id != a[j].id && ans[s].val != a[i].id && ans[s].val != a[j].id)
            {
                printf("YES\n%d %d %d %d", a[i].id, a[j].id, ans[s].id, ans[s].val);
                return 0;
            }
            else if (!ans[s].id)
                ans[s].id = a[i].id, ans[s].val = a[j].id, ++cnt;
            if (cnt >= 5e6)
            {
                puts("NO");
                return 0;
            }
        }
    puts("NO");
    return 0;
}