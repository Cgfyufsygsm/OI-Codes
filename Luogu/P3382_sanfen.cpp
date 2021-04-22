#include <cstdio>
#include <iostream>
#define eps 1e-6
using namespace std;

int n;
double k[15];
double l, r;

double ksm(double base, int p)
{
    double ans = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ans *= base;
        base *= base;
    }
    return ans;
}

double f(double x)
{
    double ans = 0;
    for (int i = 0; i <= n; i++)
    {
        double tmp = k[i] * ksm(x, i);
        ans += tmp;
    }
    return ans;
}

void search()
{
    while (r - l > eps)
    {
        double a, b;
        double t = (r - l) / 3;
        a = l + t;
        b = r - t;
        if (f(a) >= f(b))
        {
            r = b;
            continue;
        }
        else if (f(a) < f(b))
        {
            l = a;
            continue;
        }
    }
    printf("%.5lf", l);
}

int main()
{
    cin >> n >> l >> r;
    for (int i = n; i >= 0; i--)
        cin >> k[i];
    search();
    return 0;
}