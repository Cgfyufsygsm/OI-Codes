#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        using ll = long long;
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        a *= d, b *= c;
        if (a == b) puts("0");
        else if (!a || !b || a % b == 0 || b % a == 0) puts("1");
        else puts("2");
    }
    return 0;
}