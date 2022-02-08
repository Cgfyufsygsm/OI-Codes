#include <bits/stdc++.h>
#define FOR(i,a, b) for (int i = a; i <= b; ++i)

using namespace std;
string s0, s;

int main() {
    cin >> s0;
    int cnta0 = 0, cnta1 = 0;
    for (int i = 0; i < s0.size(); ++i) {
        if (s0[i] != 'a') {
            cnta0 = i;
            break;
        }
    }
    for (int i = s0.size() - 1; ~i; --i, ++cnta1) {
        if (s0[i] != 'a') break;
    }
    if (cnta0 > cnta1) return puts("No"), 0;
    for (auto c : s0) if (c != 'a') s.push_back(c);
    bool flg = 1;
    for (int i = 0; i < s.size(); ++i) flg &= (s[i] == s[s.size() - i - 1]);
    puts(flg ? "Yes" : "No");
    return 0;
}