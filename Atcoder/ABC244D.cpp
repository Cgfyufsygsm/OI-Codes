#include <bits/stdc++.h>

using namespace std;

char s[4], t[4];

int main() {
    for (int i = 1; i <= 3; ++i) cin >> s[i];
    for (int i = 1; i <= 3; ++i) cin >> t[i];
    int same = 0;
    for (int i = 1; i <= 3; ++i) same += (s[i] == t[i]);
    if (same == 3 || !same) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}