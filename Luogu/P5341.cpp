#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e5 + 5;

struct node {
    int ch[26], fa, len, size;
    void init() {
        memset(ch, 0, sizeof ch);
        fa = len = size = 0;
    }
} sam[maxn << 1];

int las, tot;

void add(int c) {
    int cur = ++tot; sam[cur].init();
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else {
            int clone = ++tot; sam[clone].init();
            sam[clone] = sam[q], sam[clone].len = sam[p].len + 1;
            while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
            sam[q].fa = sam[cur].fa = clone;
        }
    }
    las = cur;
    return;
}

char s[maxn];
int cnt[maxn << 1], sorted[maxn << 1];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        las = tot = 1;
        sam[1].init();
        memset(cnt, 0, sizeof cnt);
        int n, k;
        scanf("%s %d", s + 1, &k);
        n = strlen(s + 1);
        FOR(i, 1, n) add(s[i] - 'a');

        FOR(i, 1, tot) ++cnt[sam[i].len];
        FOR(i, 1, n) cnt[i] += cnt[i - 1];
        FOR(i, 1, tot) sorted[cnt[sam[i].len]--] = i;

        int p = 1;
        FOR(i, 1, n) p = sam[p].ch[s[i] - 'a'], sam[p].size = 1;
        DEC(i, tot, 1) sam[sam[sorted[i]].fa].size += sam[sorted[i]].size;

        memset(cnt, 0, sizeof cnt);
        FOR(i, 1, tot) if (sam[i].size == k) cnt[sam[sam[i].fa].len + 1]++, cnt[sam[i].len + 1]--;
        int ans = 0, maxx = 0;
        FOR(i, 1, n) {
            cnt[i] += cnt[i - 1];
            if (cnt[i] >= maxx) ans = i, maxx = cnt[i];
        }
        printf("%d\n", maxx ? ans : -1);
    }
    return 0;
}