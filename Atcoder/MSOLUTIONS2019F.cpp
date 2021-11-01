#include <iostream>
#include <bitset>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 2005;
bitset<maxn> L[maxn], R[maxn], a[maxn];
int n;

int main() {
    cin >> n;
    FOR(i, 1, n) {
        FOR(j, 1, i - 1) {
            char ch; cin >> ch;
            if (ch == '1') a[i][j] = 1;
            a[j][i] = a[i][j] ^ 1;
        }
    }

    FOR(i, 1, n) L[i][i] = R[i][i] = 1;
    FOR(len, 2, n) {
        FOR(i, 1, n - len + 1) {
            int j = i + len - 1;
            L[j][i] = (L[j] & R[i + 1] & a[i]).count() > 0;
            R[i][j] = (L[j - 1] & R[i] & a[j]).count() > 0;
        }
    }
    int ans = 0;
    FOR(i, 1, n) ans += (L[n][i] & R[1][i]);
    cout << ans << endl;
    return 0;
}