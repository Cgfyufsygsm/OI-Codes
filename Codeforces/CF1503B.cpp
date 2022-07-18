#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 105;
vector<pair<int, int>> vec[2];
int n;

il ostream& operator<<(ostream &ouf, const pair<int, int> &p) {
    ouf << p.first << ' ' << p.second;
    return ouf;
}

int main() {
    cin >> n;
    FOR(i, 1, n) FOR(j, 1, n) vec[(i + j) & 1].emplace_back(i, j);
    FOR(i, 1, n * n) {
        int a; cin >> a;
        if (a < 3) {
            if (vec[2 - a].size()) cout << 3 - a << ' ' << vec[2 - a].back() << endl, vec[2 - a].pop_back();
            else cout << 3 << ' ' << vec[a - 1].back() << endl, vec[a - 1].pop_back();
        } else {
            if (vec[0].size()) cout << 1 << ' ' << vec[0].back() << endl, vec[0].pop_back();
            else cout << 2 << ' ' << vec[1].back() << endl, vec[1].pop_back();
        }
    }
    return 0;
}