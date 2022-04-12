#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

const int maxn = 3e5 + 5;
using ll = long long;
int n, k;
ll b[maxn];

int N;
ll t[maxn << 2], tag[maxn << 2];

void modify(int x, int y, ll k) {
    int lNum = 0, rNum = 0, nNum = 1;
    for (x += N - 1, y += N + 1; x ^ y ^ 1; x >>= 1, y >>= 1, nNum <<= 1) {
        t[x] += k * lNum, t[y] += k * rNum;
        if (~x & 1) tag[x ^ 1] += k, t[x ^ 1] += k * nNum, lNum += nNum;
        if (y & 1) tag[y ^ 1] += k, t[y ^ 1] += k * nNum, rNum += nNum;
    }
    for (; x; x >>= 1, y >>= 1) t[x] += k * lNum, t[y] += k * rNum;
    return;
}

ll query(int x, int y) {
    int lNum = 0, rNum = 0, nNum = 1;
    ll ret = 0;
    for (x += N - 1, y += N + 1; x ^ y ^ 1; x >>= 1, y >>= 1, nNum <<= 1) {
        if (tag[x]) ret += lNum * tag[x];
        if (tag[y]) ret += rNum * tag[y];
        if (~x & 1) ret += t[x ^ 1], lNum += nNum;
        if (y & 1) ret += t[y ^ 1], rNum += nNum;
    }
    for (; x; x >>= 1, y >>= 1) ret += tag[x] * lNum + tag[y] * rNum;
    return ret;
}

int main() {
    cin >> n >> k;
    for (N = 1; N <= n + 1; N <<= 1);
    FOR(i, 1, n) cin >> b[i];
    ll ans = 0;
    DEC(i, n, k) {
        ll now = query(1, i);
        if (now < b[i]) {
            ll add = (b[i] - now + k - 1) / k;
            ans += add;
            modify(i - k + 1, i, add);
        }
    }
    DEC(i, k - 1, 1) {
        ll now = query(1, i);
        if (now < b[i]) {
            ll add = (b[i] - now + i - 1) / i;
            ans += add;
            modify(1, i, add);
        }
    }
    cout << ans << endl;
    return 0;
}