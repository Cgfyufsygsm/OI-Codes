#include <bits/stdc++.h>
#define L son[0]
#define R son[1]
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e5 + 5;

inline int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c =getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline void swap(int &a, int &b)
{
    int t = a; a = b; b = t;
    return;
}

struct node
{
    int val, son[2], rt;
} t[maxn];

int get(int x)
{
    return t[x].rt == x ? x : t[x].rt = get(t[x].rt);
}

int merge(int x, int y)
{
    static std::mt19937 rnd(20041031);
    if (!x || !y)
        return x + y;
    if (t[x].val > t[y].val || (t[x].val == t[y].val && x > y))
        swap(x, y);
    t[x].R = merge(t[x].R, y);
    if (rnd() & 1)
        swap(t[x].L, t[x].R);
    t[t[x].L].rt = t[t[x].R].rt = t[x].rt = x;
    // t[x].dis = t[t[x].R].dis + 1;
    return x;
}

void pop(int x)
{
    t[x].val = -1;
    t[t[x].L].rt = t[x].L, t[t[x].R].rt = t[x].R;
    t[x].rt = merge(t[x].L, t[x].R);
    return;
}

int n;

int main()
{
    n = read();
    int m = read();
    FOR(i, 1, n)
        t[i].rt = i, t[i].val = read();
    while (m--)
    {
        int opt = read(), x, y;
        if (opt == 1)
        {
            x = read(), y = read();
            if (t[x].val == -1 || t[y].val == -1)
                continue;
            int f1 = get(x), f2 = get(y);
            if (f1 != f2) t[f1].rt = t[f2].rt = merge(f1, f2);
        }
        else
        {
            x = read();
            if (t[x].val == -1) printf("-1\n");
            else printf("%d\n", t[get(x)].val), pop(get(x));
        }
    }
}