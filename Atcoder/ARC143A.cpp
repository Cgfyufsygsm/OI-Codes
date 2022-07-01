#include <cstdio>
#include <algorithm>

using ll = long long;
ll a[3];

int main() {
    scanf("%lld %lld %lld", a, a + 1, a + 2);
    std::sort(a, a + 3);
    ll ans = 0;
    ans += (a[1] - a[0]);
    a[2] -= (a[1] - a[0]), a[1] = a[0];
    if (a[2] - a[0] > a[0]) return puts("-1"), 0;
    ans += (2 * (a[2] - a[0]));
    ans += 2 * a[0] - a[2];
    printf("%lld\n", ans);
    return 0;
}