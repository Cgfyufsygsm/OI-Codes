#include <cstdio>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef double db;

const db eps = 1e-7, pi = acos(-1.0);
const int maxn = 10000 * 4 + 5;

il int dcmp(db x) {return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;}

struct Point
{
    db x, y;
    Point(db _x = 0, db _y = 0) {x = _x, y = _y;}
    il bool operator<(const Point &b) {return !dcmp(x - b.x) ? y < b.y : x < b.x;}
    il bool operator==(const Point &b) {return !dcmp(x - b.x) && !dcmp(y - b.y);};
} P[maxn];

typedef Point Vector;

Vector operator+(const Vector &a, const Vector &b) {return Vector(a.x + b.x, a.y + b.y);}
Vector operator-(const Vector &a, const Vector &b) {return Vector(a.x - b.x, a.y - b.y);}
db Cross(Vector a, Vector b) {return a.x * b.y - a.y * b.x;}
Vector Rotate(Vector a, db theta)
{
    db c = cos(theta), s = sin(theta);
    return Vector(a.x * c - a.y * s, a.y * c + a.x * s);
}
db Dist(Point a, Point b) {return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}

int n;

db andrew()
{
    std::sort(P + 1, P + 4 * n + 1);
    int cnt = std::unique(P + 1, P + 4 * n + 1) - P - 1;
    static int stk[maxn], top;
    FOR(i, 1, cnt)
    {
        while (top >= 2 && Cross(P[stk[top]] - P[stk[top - 1]], P[i] - P[stk[top - 1]]) < 0) --top;
        stk[++top] = i;
    }
    DEC(i, cnt - 1, 1)
    {
        while (top >= 2 && Cross(P[stk[top]] - P[stk[top - 1]], P[i] - P[stk[top - 1]]) < 0) --top;
        stk[++top] = i;
    }
    db ans = 0;
    FOR(i, 1, top - 1) ans += Dist(P[stk[i]], P[stk[i + 1]]);
    return ans;
}

int main()
{
    scanf("%d", &n);
    db a, b, r;
    scanf("%lf %lf %lf", &a, &b, &r);
    db diag = sqrt(a * a + b * b) / 2.0 - r;
    Vector R[4];
    R[0] = Vector(b / 2.0 - r, a / 2.0 - r);
    R[1] = Vector(-R[0].x, R[0].y);
    R[2] = Vector(-R[0].x, -R[0].y);
    R[3] = Vector(R[0].x, -R[0].y);
    FOR(i, 1, n)
    {
        db x, y, theta;
        scanf("%lf %lf %lf", &x, &y, &theta);
        FOR(j, 0, 3)
            P[(i - 1) * 4 + j + 1] = Point(Point(x, y) + Rotate(R[j], theta));
    }
    printf("%.2lf\n", andrew() + 2 * pi * r);
    return 0;
}