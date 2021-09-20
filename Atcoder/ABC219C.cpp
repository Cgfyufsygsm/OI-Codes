#include <iostream>
#include <string>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 50005;
string s[maxn], X;
int n, pos[26];

il bool cmp(const string &a, const string &b) {
    for (int i = 0; i < min(a.length(), b.length()); ++i) {
        if (pos[a[i] - 'a'] < pos[b[i] - 'a']) return 1;
        if (pos[a[i] - 'a'] > pos[b[i] - 'a']) return 0;
    }
    return a.length() < b.length();
}

int main() {
    cin >> X >> n;
    FOR(i, 0, 25) pos[X[i] - 'a'] = i;
    FOR(i, 1, n) cin >> s[i];
    sort(s + 1, s + n + 1, cmp);
    FOR(i, 1, n) cout << s[i] << endl;
    return 0; 
}