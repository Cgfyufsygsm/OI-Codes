#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

using ll = long long;
const int maxn = 2e5 + 5;

struct Node {
    int ch[26], fa, len;
} sam[maxn << 1];
int las = 1, tot = 1;

char s1[maxn], s2[maxn];
int n1, n2;

int sorted[maxn << 1], cnt[maxn << 1];
ll sz[maxn << 1], sum[maxn << 1];

void extend(int c) {
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
    sz[cur] = 1;
    return;
}

using ll = long long;

ll ans = 0;

int main() {
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    n1 = strlen(s1 + 1), n2 = strlen(s2 + 1);
    FOR(i, 1, n1) extend(s1[i] - 'a');

    FOR(i, 1, tot) ++cnt[sam[i].len];
    FOR(i, 1, n1) cnt[i] += cnt[i - 1];
    FOR(i, 1, tot) sorted[cnt[sam[i].len]--] = i;
    DEC(i, tot, 1) sz[sam[sorted[i]].fa] += sz[sorted[i]];
    FOR(i, 1, tot) sum[sorted[i]] += sum[sam[sorted[i]].fa] + sz[sorted[i]] * (sam[sorted[i]].len - sam[sam[sorted[i]].fa].len);

    int u = 1, len = 0;
    FOR(i, 1, n2) {
        while (u != 1 && !sam[u].ch[s2[i] - 'a']) u = sam[u].fa;
        len = min(len, sam[u].len) + 1;
        if (sam[u].ch[s2[i] - 'a']) u = sam[u].ch[s2[i] - 'a'];
        if (u != 1) ans += sum[sam[u].fa] + sz[u] * (len - sam[sam[u].fa].len);
    }

    printf("%lld\n", ans);
    return 0;
}