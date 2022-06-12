#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;
string t[maxn], s;
int n, buc[26];

int main() {
    int T; cin >> T;
    while (T --> 0) {
        memset(buc, 0, sizeof buc);
        cin >> n;
        FOR(i, 1, n << 1) cin >> t[i];
        cin >> s;
        FOR(i, 1, n << 1) for (auto &c : t[i]) buc[c - 'a']++;
        for (auto &c : s) buc[c - 'a']++;
        FOR(i, 0, 25) if (buc[i] & 1) cout << (char)(i + 'a') << endl;
    }
    return 0;
}