#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5;
int n;
struct Node {
    int a, c;
} a[maxn];
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i].a >> a[i].c;
    sort(a + 1, a + n + 1, [](const Node &a, const Node &b) {return a.a < b.a;});
    long long ans = 0;
    FOR(i, 1, n) ans += a[i].c;
    int curmx = 0;
    FOR(i, 1, n - 1) {
        chkmax(curmx, a[i].a + a[i].c);
        ans += max(0, a[i + 1].a - curmx);
    }
    cout << ans << endl;
    return 0;
}