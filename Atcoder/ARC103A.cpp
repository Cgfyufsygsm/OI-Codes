#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5, N = 1e5;

struct Node {
    int num, cnt;
} f[2][maxn];
int n;

int main() {
    cin >> n;
    FOR(i, 1, n) {
        int x; cin >> x;
        ++f[i & 1][x].cnt, f[i & 1][x].num = x;
    }
    auto cmp = [](const Node &a, const Node &b) {return a.cnt > b.cnt;};
    sort(f[0] + 1, f[0] + N + 1, cmp);
    sort(f[1] + 1, f[1] + N + 1, cmp);
    int ans = 0;
    if (f[0][1].num == f[1][1].num) ans = max(f[0][1].cnt + f[1][2].cnt, f[0][2].cnt + f[1][1].cnt);
    else ans = f[0][1].cnt + f[1][1].cnt;
    cout << n - ans << endl;
    return 0;
}