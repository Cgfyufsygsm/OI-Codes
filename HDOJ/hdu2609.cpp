#include <iostream>
#include <string>
#include <set>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

using namespace std;

set<string> S;

void work(string &s, string &t) {
    t.clear();
    int i = 0, j = 1, k = 0, n = s.size();
    while (i < n && j < n && k < n) {
        if (s[(i + k) % n] == s[(j + k) % n]) ++k;
        else {
            if (s[(i + k) % n] > s[(j + k) % n])
                i += k + 1;
            else j += k + 1;
            if (i == j) ++i;
            k = 0;
        }
    }
    int p = min(i, j);
    FOR(i, 0, n - 1) t.push_back(s[(i + p) % n]);
    return;
}

int main() {
    int n;
    string tmp1, tmp2;
    ios::sync_with_stdio(false);
    while (cin >> n) {
        S.clear();
        FOR(i, 1, n) {
            cin >> tmp1;
            work(tmp1, tmp2);
            S.insert(tmp2);
        }
        cout << S.size() << endl;
    }
    return 0;
}