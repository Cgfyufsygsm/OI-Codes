#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define il inline

typedef long long ll;

const int maxn = 5e5 + 5;

struct node {
    int ch[26], fa, len;
} sam[maxn << 1];

int t, k, len, tot = 1, las = 1;
ll size[maxn << 1], sum[maxn << 1];
char s[maxn];

void add(int c) {
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1, size[cur] = 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else {
            int clone = ++tot;
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1, size[clone] = 0;
            while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
            sam[q].fa = sam[cur].fa = clone;
        }
    }
    las = cur;
    return;
}

int buc[maxn], a[maxn << 1];

void print(int x, int k) {
    if (k <= size[x]) return;
    k -= size[x];
    FOR(c, 0, 25) {
        int y = sam[x].ch[c];
        if (!y) continue;
        if (k > sum[y]) {
            k -= sum[y];
            continue;
        }
        putchar(c + 'a'); print(y, k); return;
    }
}

int main() {
    scanf("%s", s + 1);
    scanf("%d %d", &t, &k);
    len = strlen(s + 1);
    FOR(i, 1, len) add(s[i] - 'a');

    FOR(i, 1, tot) ++buc[sam[i].len];
    FOR(i, 1, len) buc[i] += buc[i - 1];
    FOR(i, 1, tot) a[buc[sam[i].len]--] = i;
    DEC(i, tot, 1) size[sam[a[i]].fa] += size[a[i]];
    FOR(i, 1, tot) t ? (sum[i] = size[i]) : (sum[i] = size[i] = 1);
    size[1] = sum[1] = 0;
    DEC(i, tot, 1)
        FOR(c, 0, 25)
            if (sam[a[i]].ch[c])
                sum[a[i]] += sum[sam[a[i]].ch[c]];
    if (sum[1] < k) puts("-1");
    else print(1, k);
    return 0;
}