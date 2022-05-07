#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using db = long double;
const db EPS = 1e-6;
const int maxn = 505;

vector<db> vec[maxn], a[maxn];
int n, m, tot, ans;

int main() {
    cin >> n >> m;;
    FOR(i, 1, n) {
        vec[i].resize(m + 1);
        FOR(j, 1, m) cin >> vec[i][j];
    }
    FOR(i, 1, m) a[i].resize(m + 1);
    FOR(i, 1, n) cin >> vec[i][0];
    sort(vec + 1, vec + n + 1, [](const auto &a, const auto &b) {return a[0] < b[0];});
    FOR(u, 1, n) {
        FOR(i, 1, m) {
            if (fabs(a[i][i]) < EPS) continue;
            db div = vec[u][i] / a[i][i];
            FOR(j, i, m) vec[u][j] -= a[i][j] * div;
        }
        int pos = -1;
        FOR(i, 1, m) if (fabs(vec[u][i]) > EPS) {
            pos = i;
            break;
        }
        if (~pos) {
            ans += vec[u][0], ++tot;
            a[pos] = vec[u];
        }
    }
    cout << tot << ' ' << ans << endl;
    return 0;
}