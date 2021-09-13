#include <iostream>
#include <string>

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

int main() {
    ios::sync_with_stdio(false);
    cin >> s >> t;
    for (auto c : s) add(c - 'a');
    int ans = 0, len = 0, p = 1;
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
        ans = max(ans, len);
    }
    cout << ans << endl;
}