#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 3e5 + 5;
char s[maxn], t[maxn];
int a[maxn], b[maxn], sum[maxn], n;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        cin >> (s + 1) >> (t + 1);
        FOR(i, 1, n) a[i] = s[i] - '0', b[i] = t[i] - '0', sum[i] = sum[i - 1] + a[i];
        int rev = 0, flg = 1;
        DEC(i, n, 1) {
            if ((a[i] ^ rev) != b[i]) {
                if (sum[i] * 2 == i) rev ^= 1;
                else {
                    flg = 0;
                    break;
                }
            }
        }
        puts(flg ? "YES" : "NO");
    }
    return 0;
}