#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 505;
int n, m;
char s[maxn][maxn];

const int fx[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int fy[] = {0, 1, -1, 1, -1, 0, 1, -1};

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        FOR(i, 1, n) cin >> s[i] + 1;
        int flg = 0, cnt = 0;
        FOR(i, 1, n) FOR(j, 1, m) {
            if (s[i][j] == '0') {
                FOR(k, 0, 7) {
                    int x = i + fx[k], y = j + fy[k];
                    if (x <= n && x >= 1 && y <= m && y >= 1 && s[x][y] == '0') flg = 1;
                }
            } else ++cnt;
        }
        cout << (flg ? cnt : (cnt == n * m ? cnt - 2 : cnt - 1)) << endl;
    }
    return 0;
}