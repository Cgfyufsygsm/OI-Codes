#include <cstdio>

typedef long long ll;

ll f(ll a, ll b, ll c, ll n) {
    if (!a) return (n + 1) * (b / c);
    if (a >= c || b >= c) return n * (n + 1) / 2 * (a / c) + (n + 1) * (b / c) + f(a % c, b % c, c, n);
    int m = (a * n + b) / c;
    return n * m - f(c, c - b - 1, a, m - 1);
}

int main() {
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    if (b < a) {int t = b; b = a, a = t;}
    printf("%lld\n", c / a + 1 + f(b - a, c, b, c / a) - (c / a) * (c / a + 1) / 2);
    return 0;
}