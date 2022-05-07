#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 1e6 + 5;

struct Node {
    int ch[26], len, fa;
} sam[maxn];

long long ans = 0;
int las = 1, tot = 1;
char s[maxn];

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
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    FOR(i, 1, n) add(s[i] - 'a');
    FOR(i, 1, tot) ans += sam[i].len - sam[sam[i].fa].len;
    printf("%lld\n", ans);
    return 0;
}