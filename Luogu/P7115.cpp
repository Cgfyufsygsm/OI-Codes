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

template<typename T> inline void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 55, maxm = 405, maxt = 820005;
int a[maxn][maxm], cnt[maxn], p[maxn], n, m;
int opt, X[maxt], Y[maxt];

void move(int x, int y)
{
    X[++opt] = x, Y[opt] = y;
    a[y][++cnt[y]] = a[x][cnt[x]--];
    return;
}

int count(int idx, int x)
{
    int ret = 0;
    FOR(i, 1, cnt[idx])
        ret += (a[idx][i] == x);
    return ret;
}

inline int top(int idx)
{
    return a[idx][cnt[idx]];
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n)
    {
        cnt[i] = m;
        FOR(j, 1, m)
            a[i][j] = read();
    }
    FOR(i, 1, n + 1)
        p[i] = i;
    DEC(now, n, 3)
    {
        int tmp = count(p[1], now);
        FOR(i, 1, tmp) move(p[now], p[now + 1]);
        FOR(i, 1, m)
            if (top(p[1]) == now)
                move(p[1], p[now]);
            else move(p[1], p[now + 1]);
        FOR(i, 1, m - tmp) move(p[now + 1], p[1]);
        FOR(i, 1, m)
            if (top(p[2]) == now || cnt[p[1]] == m)
                move(p[2], p[now + 1]);
            else move(p[2], p[1]);
        swap(p[1], p[now]);
        swap(p[2], p[now + 1]);
        FOR(k, 1, now - 1)
        {
            tmp = count(p[k], now);
            FOR(i, 1, tmp) move(p[now], p[now + 1]);
            FOR(i, 1, m)
                if (top(p[k]) == now)
                    move(p[k], p[now]);
                else move(p[k], p[now + 1]);
            swap(p[k], p[now + 1]);
            swap(p[k], p[now]);
        }
        FOR(i, 1, now - 1)
            while (top(p[i]) == now)
                move(p[i], p[now + 1]);
        FOR(i, 1, now - 1)
            while (cnt[p[i]] < m)
                move(p[now], p[i]);
    }
    
    int tmp = count(p[1], 1);
    FOR(i, 1, tmp)
        move(p[2], p[3]);
    FOR(i, 1, m)
        if (top(p[1]) == 1) move(p[1], p[2]);
        else move(p[1], p[3]);
    FOR(i, 1, tmp)
        move(p[2], p[1]);
    FOR(i, 1, m - tmp)
        move(p[3], p[1]);
    while (cnt[p[3]]) move(p[3], p[2]);
    FOR(i, 1, m - tmp)
        move(p[1], p[3]);
    FOR(i, 1, m)
        if (top(p[2]) == 1)
            move(p[2], p[1]);
        else move(p[2], p[3]);
    printf("%d\n", opt);
    FOR(i, 1, opt)
        printf("%d %d\n", X[i], Y[i]);
    return 0;
}