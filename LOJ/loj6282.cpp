#include <cstdio>
#include <cctype>
#include <cmath>
#include <vector>
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

const int maxn = 2e5 + 5;
std::vector<int> vec[maxn];
int tmp[maxn], n, m, block;

void rebuild()
{
    int cnt = 0;
    FOR(i, 1, m)
    {
        for (auto x : vec[i])
            tmp[++cnt] = x;
        vec[i].clear();
    }
    block = sqrt(cnt);
    FOR(i, 1, cnt)
        vec[(i - 1) / block + 1].push_back(tmp[i]);
    m = (cnt - 1) / block + 1;
}

il void getpos(int x, int &i, int &j)
{
    for (i = 1; x > vec[i].size(); x -= vec[i++].size());
    j = x - 1;
    return;
}

void ins(int x, int val)
{
    int i, j;
    getpos(x, i, j);
    vec[i].insert(vec[i].begin() + j, val);
    if (vec[i].size() > 5 * block)
        rebuild();
}

int query(int x)
{
    int i, j;
    getpos(x, i, j);
    return vec[i][j];
}

int main()
{
    block = sqrt(n = read());
    FOR(i, 1, n)
        vec[(i - 1) / block + 1].push_back(read());
    m = (n - 1) / block + 1;
    reg int opt, l, r;
    FOR(k, 1, n)
    {
        opt = read(), l = read(), r = read(), read();
        if (opt == 0)
            ins(l, r);
        else printf("%d\n", query(r));
    }
    return 0;
}