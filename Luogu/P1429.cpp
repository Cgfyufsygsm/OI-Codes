#include <cstdio>
#include <cmath>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef double db;

const int maxn = 200000 + 5;

template<typename T> inline T min(T a, T b) {return a < b ? a : b;}

struct Point
{
    db x, y;
    bool operator<(const Point &b) const
    {
        return x == b.x ? y < b.y : x < b.x;
    }
} p[maxn];

inline db dist(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int n;

db work(int l, int r)
{
    if (l >= r) return 1e9;
    if (r - l == 1)
        return dist(p[l], p[r]);
    int mid = (l + r) >> 1;
    db tmp = min(work(l, mid), work(mid + 1, r)), ans = tmp;
    db axis = (p[mid].x + p[mid + 1].x) / 2;
    DEC(i, mid, l)
    {
        if (axis - p[i].x >= tmp) break;
        FOR(j, mid + 1, r)
        {
            if (fabs(p[j].y - p[i].y) >= tmp) continue;
            if (p[j].x - p[i].x >= tmp) break;
            ans = min(ans, dist(p[i], p[j]));
        }
    }
    return ans;
}

int main()
{
    scanf("%d", &n);
    FOR(i, 1, n)
        scanf("%lf %lf", &p[i].x, &p[i].y);
    std::sort(p + 1, p + n + 1);
    printf("%.4lf\n", work(1, n));
    return 0;
}