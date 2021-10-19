#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

string s[1005];

int main() {
    cin >> s[1];
    FOR(i, 2, s[1].length())
        s[i] = s[1].substr(i - 1) + s[1].substr(0, i - 1);
    sort(s + 1, s + s[1].length() + 1);
    cout << s[1] << endl << s[s[1].length()] << endl;
    return 0;
}