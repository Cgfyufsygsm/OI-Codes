#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 5e5 + 5;
int n, sg[maxn];
char s[maxn];

void prework() {
    sg[0] = sg[1] = 0;
    FOR(n, 2, 100) {
        set<int> S;
        FOR(i, 0, n - 2) S.insert(sg[i] ^ sg[n - 2 - i]);
        for (int i = 0; ; ++i) if (!S.count(i)) {
            sg[n] = i;
            break;
        }
    }
    FOR(n, 101, (int)5e5) sg[n] = sg[n - 34];
    return;
}

int main() {
    prework();
    int T; cin >> T;
    while (T--) {
        cin >> n >> (s + 1);
        int cntR = 0;
        FOR(i, 1, n) cntR += (s[i] == 'R');
        if (cntR > n - cntR) puts("Alice");
        else if (cntR < n - cntR) puts("Bob");
        else {
            int ans = 0;
            for (int i = 1, j; i <= n; i = j) { // [i, j)
                j = i + 1;
                while (j <= n && s[j] != s[j - 1]) ++j;
                ans ^= sg[j - i];
            }
            puts(ans ? "Alice" : "Bob");
        }
    }
    return 0;
}