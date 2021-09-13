#include <iostream>
#include <string>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e6 + 5;
string s, t[maxn];

struct node {
    int ch[26], len, fa;
} sam[maxn << 1];

int las = 1, tot = 1;

void add(int c) {
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else {
            int clone = ++tot;
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1;
            while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
            sam[q].fa = sam[cur].fa = clone;
        }
    }
    las = cur;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    FOR(i, 1, n) cin >> t[i];
    cin >> s;
    for (auto c : s) add(c - 'a');
    int ans = 0;
    FOR(i, 1, n) {
        int p = 1;
        for (auto c : t[i]) {
            p = sam[p].ch[c - 'a'];
            if (!p) break;
        }
        if (p) ++ans;
    }
    cout << ans << endl;
    return 0;
}