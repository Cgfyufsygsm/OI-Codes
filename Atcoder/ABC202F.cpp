#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 85;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

struct Point
{
    int x, y;
    Point() {}
    Point(int _x, int _y) {x = _x, y = _y;}
    il bool operator<(const Point &b) const {return x == b.x ? y < b.y : x < b.x;}
} P[maxn];

typedef Point Vector;

struct modint
{
    typedef long long ll;
    const static ll mod = 1e9 + 7;
    ll val;
    modint(int _val = 0) {val = _val;}
    modint operator+(const modint &b) const {return modint((val + b.val) % mod);}
    modint operator-(const modint &b) const {return modint((val - b.val + mod) % mod);}
    modint operator*(const modint &b) const {return modint((val * b.val) % mod);}
    modint operator+=(const modint &b) {return *this = *this + b;}
    modint operator*=(const modint &b) {return *this = *this * b;}
    modint operator-=(const modint &b) {return *this = *this - b;}
    modint operator+(const int &b) const {return modint((val + b) % mod);}
    modint operator-(const int &b) const {return modint((val - b + mod) % mod);}
    modint operator*(const int &b) const {return modint((val * b) % mod);}
    modint operator+=(const int &b) {return *this = *this + b;}
    modint operator-=(const int &b) {return *this = *this - b;}
    modint operator*=(const int &b) {return *this = *this * b;}
};

il Vector operator-(const Point &a, const Point &b) {return Point(b.x - a.x, b.y - a.y);}
il int operator^(const Vector &a, const Vector &b) {return a.x * b.y - a.y * b.x;}

int area2(Point x, Point y, Point z)
{
    return abs((y - x) ^ (z - x));
}

int n, parity[maxn][maxn][maxn], inside[maxn][maxn][maxn];
modint pow2[maxn], upper[maxn][maxn][2], lower[maxn][maxn][2];

int main()
{
    n = read();
    FOR(i, 1, n) P[i].x = read(), P[i].y = read();
    std::sort(P + 1, P + n + 1);

    FOR(i, 1, n)
        FOR(j, 1, n)
            FOR(k, 1, n)
            {
                if (i == j || j == k || i == k) continue;
                parity[i][j][k] = area2(P[i], P[j], P[k]) % 2;
                FOR(l, 1, n)
                    if (l != i && l != j && l != k && area2(P[i], P[j], P[k]) == area2(P[l], P[j], P[k]) + area2(P[i], P[l], P[k]) + area2(P[i], P[j], P[l]))
                        inside[i][j][k] += 1;
            }
    

    pow2[0] = 1;
    FOR(i, 1, n) pow2[i] = pow2[i - 1] * 2;

    modint ans = 0;

    DEC(must, n, 1)
    {
        FOR(i, must, n)
            FOR(j, must, n)
                FOR(k, 0, 1)
                    upper[i][j][k] = lower[i][j][k] = 0;
        FOR(i, must + 1, n) upper[must][i][0] = lower[must][i][0] = 1;
        FOR(i, must, n)
            FOR(j, must + 1, n)
                FOR(k, 0, 1)
                    FOR(l, j + 1, n)
                        if (((P[l] - P[j]) ^ (P[j] - P[i])) > 0)
                            upper[j][l][k ^ parity[must][j][l]] += upper[i][j][k] * pow2[inside[must][j][l]];
                        else lower[j][l][k ^ parity[must][j][l]] += lower[i][j][k] * pow2[inside[must][j][l]];
        FOR(j, must + 1, n)
            FOR(k, 0, 1)
            {
                modint up = 0, lo = 0;
                FOR(i, must, j - 1)
                    up += upper[i][j][k], lo += lower[i][j][k];
                ans += up * lo;
            }
    }

    printf("%d\n", (ans - n * (n - 1) / 2).val);
    return 0;
}