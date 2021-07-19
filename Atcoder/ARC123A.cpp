#include <cstdio>
#include <cmath>

typedef long long ll;
ll a, b, c;

ll myabs(ll x) {return x >= 0 ? x : -x;}
ll min(ll a, ll b) {return a < b ? a : b;}

int main() {
    scanf("%lld %lld %lld", &a, &b, &c);
    ll d = b - a, e = c - b;
    if (d == e) return puts("0"), 0;
    if (a < c) {
        if (e > d) {
            if ((a + c) & 1)
                printf("%lld\n", 1 + (a + c + 1) / 2 - b);
            else printf("%lld\n", (a + c) / 2 - b);
        } else printf("%lld\n", d - e);
    } else if (a == c) {
        if (b < c) printf("%lld\n", c - b);
        else printf("%lld\n", 2 * (b - c));
    } else {
        if (e > d) {
             if ((a + c) & 1)
                printf("%lld\n", 1 + (a + c + 1) / 2 - b);
            else printf("%lld\n", (a + c) / 2 - b);
        } else printf("%lld\n", d - e);
    }
    return 0;
}