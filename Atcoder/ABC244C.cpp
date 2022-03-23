#include <bits/stdc++.h>

using namespace std;

set<int> S;
int n;

int main() {
    cin >> n;
    for (int i = 1; i <= 2 * n + 1; ++i) S.insert(i);
    while (!S.empty()) {
        cout << *S.begin() << endl;
        S.erase(S.begin());
        int x; cin >> x;
        S.erase(x);
    }
    return 0;
}