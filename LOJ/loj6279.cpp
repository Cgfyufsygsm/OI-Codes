#include <bits/stdc++.h>
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

il long long min(long long a, long long b) {return a < b ? a : b;}
il long long max(long long a, long long b) {return a > b ? a : b;}

using namespace std;

const int maxn = 1e5 + 5;
int n, a[maxn], tag[maxn], bl[maxn], block;
set<int, greater<int> > s[maxn];

void add(int l, int r, int val)
{
    FOR(i, l, min(bl[l] * block, r))
    {
        s[bl[l]].erase(a[i]);
        s[bl[l]].insert(a[i] = a[i] + val);
    }
    if (bl[l] != bl[r])
    {
        FOR(i, (bl[r] - 1) * block + 1, r)
        {
            s[bl[r]].erase(a[i]);
            s[bl[r]].insert(a[i] = a[i] + val);
        }
    }
    FOR(i, bl[l] + 1, bl[r] - 1)
        tag[i] += val;
    return;
}

int query(int l, int r, int val)
{
    long long ret = -1e18;
    FOR(i, l, min(bl[l] * block, r))
        if (a[i] + tag[bl[l]] < val)
            ret = max(a[i] + tag[bl[l]], ret);
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            if (a[i] + tag[bl[r]] < val)
                ret = max(a[i] + tag[bl[r]], ret);
    FOR(i, bl[l] + 1, bl[r] - 1)
    {
        int tmp = val - tag[i];
        set<int>::iterator it = s[i].upper_bound(tmp);
        if (it != s[i].end())
            ret = max(ret, (*it) + tag[i]);
    }
    return ret < -1e10 ? -1 : ret;
}

int main()
{
    block = sqrt(n = read());
    FOR(i, 1, n)
        a[i] = read(), bl[i] = (i - 1) / block + 1, s[bl[i]].insert(a[i]);
    reg int opt, l, r, c;
    FOR(i, 1, n)
    {
        opt = read(), l = read(), r = read(), c = read();
        if (opt == 0)
            add(l, r, c);
        else
            printf("%d\n", query(l, r, c));
    }
    return 0;
}