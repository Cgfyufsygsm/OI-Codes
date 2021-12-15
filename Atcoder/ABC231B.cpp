#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

using namespace std;

map<string, int> mp;
string ans;
int tmp;

int main() {
    int n; cin >> n;
    FOR(i, 1, n) {
        string s; cin >> s;
        if (mp.count(s)) ++mp[s];
        else mp[s] = 1;
    }
    tmp = 0;
    for (auto &p : mp) if (p.second > tmp) ans = p.first, tmp = p.second;
    cout << ans << endl;
    return 0;
}