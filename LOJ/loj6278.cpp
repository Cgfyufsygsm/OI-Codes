#include <cstdio>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
#define reg register
#define il inline
#define FOR(i, a, b) for (reg int i = a; i <= b; ++i)

il int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

il int min(int a, int b) {return a < b ? a : b;}

const int maxn = 50005;
int n, a[maxn], bl[maxn], tag[maxn], block;
std::vector<int> vec[maxn];

void reset(int x)
{
    vec[x].clear();
    FOR(i, (x - 1) * block + 1, min(x * block,  n))
        vec[x].push_back(a[i]);
    std::sort(vec[x].begin(), vec[x].end());
    return;
}

void add(int l, int r, int val)
{
    FOR(i, l, min(bl[l] * block, r))
        a[i] += val;
    reset(bl[l]);
    if (bl[l] != bl[r])
    {
        FOR(i, (bl[r] - 1) * block + 1, r)
            a[i] += val;
        reset(bl[r]);
    }
    FOR(i, bl[l] + 1, bl[r] - 1)
        tag[i] += val;
    return;
}

int query(int l, int r, int val)
{
    int ret = 0;
    FOR(i, l, min(bl[l] * block, r))
        ret += (a[i] + tag[bl[l]] < val);
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            ret += (a[i] + tag[bl[r]] < val);
    FOR(i, bl[l] + 1, bl[r] - 1)
    {
        int tmp = val - tag[i];
        ret += (std::lower_bound(vec[i].begin(), vec[i].end(), tmp) - vec[i].begin());
    }
    return ret;
}

int main()
{
    n = read();
    block = sqrt(n);
    FOR(i, 1, n)
        a[i] = read(), bl[i] = (i - 1) / block + 1;
    FOR(i, 1, bl[n])
        reset(i);
    reg int opt, l, r, c;
    FOR(m, 1, n)
    {
        opt = read(), l = read(), r = read(), c = read();
        if (!opt)
            add(l, r, c);
        else
            printf("%d\n", query(l, r, c * c));
    }
    return 0;
}