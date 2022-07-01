#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const char ch[4] = {'A', 'T', 'C', 'G'};
const int maxn = 1e5 + 5;

struct Node {
    int ch[4], fa, len;
} sam[maxn << 1];
int las = 1, tot = 1, ans, n;

int f[maxn << 1], cnt[maxn], sorted[maxn << 1];
char s[maxn];

void extend(int c) {
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
    f[cur] = 1;
    return;
}

void dfs(int u, int i, int used) {
    if (i > n) return (void)(ans += f[u]);
    FOR(c, 0, 3) {
        if (!sam[u].ch[c]) continue;
        if (ch[c] == s[i]) dfs(sam[u].ch[c], i + 1, used);
        else if (used < 3) dfs(sam[u].ch[c], i + 1, used + 1);
    }
    return;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        las = tot = 1, ans = 0;
        scanf("%s", s + 1);
        n = strlen(s + 1);
        memset(cnt, 0, sizeof cnt);
        memset(f, 0, sizeof f);
        memset(sorted, 0, sizeof sorted);
        memset(sam, 0, sizeof sam);
        FOR(i, 1, n) FOR(k, 0, 3) if (ch[k] == s[i]) extend(k);

        FOR(i, 1, tot) ++cnt[sam[i].len];
        FOR(i, 1, n) cnt[i] += cnt[i - 1];
        FOR(i, 1, tot) sorted[cnt[sam[i].len]--] = i; 
        DEC(i, tot, 1) f[sam[sorted[i]].fa] += f[sorted[i]];

        scanf("%s", s + 1);
        n = strlen(s + 1);
        dfs(1, 1, 0);
        printf("%d\n", ans);
    }
    return 0;
}