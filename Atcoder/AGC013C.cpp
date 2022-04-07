#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5;
int T, L, N, x[maxn], d[maxn], cnt;

int main() {
    cin >> N >> L >> T;
    FOR(i, 0, N - 1) {
        cin >> x[i] >> d[i];
        x[i] += (d[i] == 1 ? T : -T);
        cnt = (cnt + (int)floor(1.0 * x[i] / L) % N + N) % N;
        x[i] = (x[i] % L + L) % L;
    }
    sort(x, x + N);
    FOR(i, 0, N - 1) cout << x[(i + cnt) % N] << endl;
    return 0;
}