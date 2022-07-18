#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
using namespace std;
const int maxn = 2e5 + 5;
int n, a[maxn], b[maxn], pos1[maxn], pos2[maxn];
char s1[maxn], s2[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        cin >> (s1 + 1) >> (s2 + 1);
        s1[0] = s2[0] = '0';
        FOR(i, 2, n) a[i] = s1[i] ^ s1[i - 1], b[i] = s2[i] ^ s2[i - 1];
        int cnt1 = 0, cnt2 = 0;
        FOR(i, 2, n) if (a[i]) pos1[++cnt1] = i;
        FOR(i, 2, n) if (b[i]) pos2[++cnt2] = i;
        if (cnt1 != cnt2 || s1[1] != s2[1]) cout << -1 << '\n';
        else {
            long long ans = 0;
            FOR(i, 1, cnt1) ans += myabs(pos1[i] - pos2[i]);
            cout << ans << '\n';
        }
    }
    return 0;
}