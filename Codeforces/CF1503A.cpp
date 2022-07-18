#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;
int n;
char s[maxn], ans1[maxn], ans2[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> (s + 1);
        vector<int> pos[2];
        FOR(i, 1, n) pos[s[i] - '0'].emplace_back(i);
        if ((pos[0].size() & 1) || (pos[1].size() & 1) || pos[1].empty() || (pos[1].front() != 1) || (pos[1].back() != n)) {
            puts("NO");
            continue;
        }
        int i = 0, j = pos[1].size() - 1;
        while (i < j) {
            ans1[pos[1][i]] = '(', ans2[pos[1][i]] = '(';
            ans1[pos[1][j]] = ')', ans2[pos[1][j]] = ')';
            ++i, --j; 
        }
        int rev = 0;
        for (auto &x : pos[0]) {
            ans1[x] = '(' ^ rev, ans2[x] = ')' ^ rev;
            rev ^= 1;
        }
        puts("YES");
        FOR(i, 1, n) putchar(ans1[i]); putchar('\n');
        FOR(i, 1, n) putchar(ans2[i]); putchar('\n');
    }
    return 0;
}