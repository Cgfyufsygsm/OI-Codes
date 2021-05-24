#include <cstdio>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef double db;

const int maxn = 1e5 + 5;
const db eps = 1e-7;

il int dcmp(db x)
{
    return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);
}

struct Point
{
    db x, y, p;
    Point() {}
    Point(db _x, db _y) {x = _x, y = _y;}
} p[maxn];

il bool cmp(Point a, Point b)
{
    return dcmp(a.x - b.x) ? a.x < b.x : a.y < b.y;
}

typedef Point Vector;

il Vector getVec(Point a, Point b) {return Point(b.x - a.x, b.y - a.y);}
il db operator^(Vector a, Vector b) {return a.x * b.y - a.y * b.x;}
il db dist(Point a, Point b) {return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));}

int n;

int stk[maxn], top;

int main()
{
    scanf("%d", &n);
    FOR(i, 1, n)
    {
        db x, y;
        scanf("%lf %lf", &x, &y);
        p[i] = Point(x, y);
    }
    std::sort(p + 1, p + n + 1, cmp);
    db ans = 0;
    FOR(i, 1, n)
    {
        while (top >= 2 && (getVec(p[stk[top - 1]], p[stk[top]]) ^ getVec(p[stk[top - 1]], p[i])) < 0) --top;
        stk[++top] = i;
    }
    DEC(i, n - 1, 1)
    {
        while (top >= 2 && (getVec(p[stk[top - 1]], p[stk[top]]) ^ getVec(p[stk[top - 1]], p[i])) < 0) --top;
        stk[++top] = i;
    }
    FOR(i, 1, top - 1) ans += dist(p[stk[i]], p[stk[i + 1]]);
    printf("%.2lf\n", ans);
    return 0;
}