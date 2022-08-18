#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

il int query(int a, int b) {
    cout << "? " << a << ' ' << b << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> vec;
        FOR(i, 1, (1 << n)) vec.emplace_back(i);
        while (vec.size() >= 4) {
            vector<int> nxt;
            for (int i = 0; i * 4 + 3 < vec.size(); ++i) {
                int a = vec[4 * i], b = vec[4 * i + 1], c = vec[4 * i + 2], d = vec[4 * i + 3];
                int r = query(a, c);
                if (r == 0) {
                    r = query(b, d);
                    if (r == 1) nxt.emplace_back(b);
                    else nxt.emplace_back(d);
                } else if (r == 1) {
                    r = query(a, d);
                    if (r == 1) nxt.emplace_back(a);
                    else nxt.emplace_back(d);
                } else if (r == 2) {
                    r = query(b, c);
                    if (r == 1) nxt.emplace_back(b);
                    else nxt.emplace_back(c);
                }
            }
            vec = nxt;
        }
        if (vec.size() >= 2) {
            int r = query(vec[0], vec[1]);
            if (r == 1) vec = {vec[0]};
            else vec = {vec[1]};
        }
        cout << "! " << vec[0] << '\n';
        cout.flush();
    }
    return 0;
}