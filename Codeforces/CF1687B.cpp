#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 205, maxm = 505;
int n, m, q[maxm], w[maxm], id[maxm];

int query() {
    cout << "? ";
    FOR(i, 1, m) cout << q[i];
    cout << endl;
    int ret; cin >> ret;
    return ret;
}

int main() {
    cin >> n >> m;
    FOR(p, 1, m) {
        q[p - 1] = 0, q[p] = 1;
        w[p] = query();
        id[p] = p;
    }
    sort(id + 1, id + m + 1, [](const int &a, const int &b) {return w[a] < w[b];});
    int last = 0;
    memset(q, 0, sizeof q);
    FOR(i, 1, m) {
        q[id[i]] = 1;
        int cur = query();
        if (cur - last == w[id[i]]) last = cur;
        else q[id[i]] = 0;
    }
    cout << "! " << last << endl;
    return 0;
}