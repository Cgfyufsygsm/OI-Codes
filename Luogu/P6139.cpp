#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 2e6 + 5;

struct Node {
    int ch[26], fa, len;
} sam[maxn];

int tot = 1, las = 1;

void extend(int c) {
    auto split = [&c](int p, int q) {
        int clone = ++tot;
        sam[clone] = sam[q];
        sam[clone].len = sam[p].len + 1;
        while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
        return sam[q].fa = clone;
    };
    if (sam[las].ch[c]) {
        int q = sam[las].ch[c];
        if (sam[q].len == sam[las].len + 1) las = q;
        else las = split(las, q);
        return;
    }
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else sam[cur].fa = split(p, q);
    }
    las = cur;
    return;
}

int n;
char s[maxn];

int main() {
    scanf("%d", &n);
    FOR(i, 1, n) {
        las = 1;
        scanf("%s", s + 1);
        for (int j = 1; s[j]; ++j) extend(s[j] - 'a');
    }
    long long ans = 0;
    FOR(i, 2, tot) ans += sam[i].len - sam[sam[i].fa].len;
    printf("%lld\n", ans);
    return 0;
}