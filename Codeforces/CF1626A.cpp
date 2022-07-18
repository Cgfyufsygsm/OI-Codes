#include <bits/stdc++.h>

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        sort(s.begin(), s.end());
        cout << s << endl;
    }
    return 0;
}