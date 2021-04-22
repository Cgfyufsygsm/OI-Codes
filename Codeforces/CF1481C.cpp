#include <cstdio>
#include <cctype>
#include <vector>
#include <map>
#include <cstring>
#define init(a) memset((a), 0, sizeof (a))
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define YES printf("YES\n")
#define NO printf("NO\n")

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

const int maxn = 1e5 + 5;

int n, m;
int a[maxn], b[maxn], c[maxn], arr[maxn], vis[maxn];

std::map<int, std::vector<int> > Map1, Map2;

int main()
{
    int T = read();
    while (T--)
    {
        Map1.clear();
        Map2.clear();
        init(vis);
        n = read(), m = read();
        FOR(i, 1, n) a[i] = read();
        FOR(i, 1, n)
        {
            b[i] = read();
            if (a[i] != b[i]) Map1[b[i]].push_back(i);
            else Map2[b[i]].push_back(i);
        }
        FOR(i, 1, m) c[i] = read();
        bool x1 = Map1.count(c[m]), x2 = Map2.count(c[m]);
        if (!x1 && !x2)
        {
            NO;
            continue;
        }
        int tmp;
        if (x1)
        {
            tmp = Map1[c[m]].back();
            arr[m] = tmp;
            vis[tmp] = 1;
            Map1[c[m]].pop_back();
        }
        else
        {
            tmp = Map2[c[m]].back();
            arr[m] = tmp;
            vis[tmp] = 1;
            Map2[c[m]].pop_back();
        }
        DEC(i, m - 1, 1)
        {
            if ((!Map1.count(c[i])) || Map1[c[i]].empty())
                arr[i] = tmp;
            else
            {
                arr[i] = Map1[c[i]].back();
                vis[arr[i]] = 1;
                Map1[c[i]].pop_back();
            }
        }
        bool flag = 1;
        FOR(i, 1, n)
        {
            vis[i] |= (a[i] == b[i]);
            flag &= vis[i];
        }
        if (!flag) NO;
        else
        {
            YES;
            FOR(i, 1, m)
                printf("%d ", arr[i]);
            printf("\n");
        }
    }
    return 0;
}