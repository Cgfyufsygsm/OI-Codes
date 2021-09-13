#include <iostream>
#include <cstring>
#include <string>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

string s, t;

const int maxn = 2.5e5 + 5;

struct node {
    int ch[26], fa, len;
} sam[maxn << 1];

int tot = 1, las = 1;

void add(int c) {
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1)
            sam[cur].fa = q;
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

int cnt[maxn << 1], sorted[maxn << 1];
int mn[maxn << 1], mx[maxn << 1];

int main() {
    ios::sync_with_stdio(false);
    cin >> s;
    for (auto c : s) add(c - 'a');
    FOR(i, 1, tot) ++cnt[sam[i].len];
    FOR(i, 1, tot) cnt[i] += cnt[i - 1];
    FOR(i, 1, tot) sorted[cnt[sam[i].len]--] = i;

    memset(mn, 0x3f, sizeof mn);

    while (cin >> t) {
        memset(mx, 0, sizeof mx);
        int p = 1, len = 0;
        for (auto ch : t) {
            int c = ch - 'a';
            if (!sam[p].ch[c]) {
                while (p != 1 && !sam[p].ch[c]) p = sam[p].fa;
                len = sam[p].len;
            }
            if (sam[p].ch[c]) {
                p = sam[p].ch[c];
                ++len;
            }
            mx[p] = max(mx[p], len);
        }
        DEC(i, tot, 1) {
            int u = sorted[i], fa = sam[u].fa;
            mx[fa] = max(mx[fa], min(sam[fa].len, mx[u]));
            mn[u] = min(mn[u], mx[u]);
        }
    }

    int ans = 0;
    FOR(i, 1, tot) ans = max(ans, mn[i]);
    cout << ans << endl;
    return 0;
}