#include <iostream>
#include <string>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

string s[4], t;

int main() {
    FOR(i, 1, 3) cin >> s[i];
    cin >> t;
    for (auto ch : t) cout << s[ch - '0'];
    return 0; 
}