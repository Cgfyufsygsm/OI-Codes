#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

int main() {
    map<int, int> mapping;
    FOR(i, 1, 30) mapping[1 << i] = i;
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> vec[2];
        FOR(i, 1, n) {
            int x; cin >> x;
            vec[x & 1].push_back(x);
        }
        if (vec[1].size()) {
            cout << vec[0].size() << endl;
        } else {
            int mind = 1e9;
            for (auto &x : vec[0]) mind = min(mind, mapping[(x & -x)]);
            cout << mind + vec[0].size() - 1 << endl;
        }
    }
    return 0;
}