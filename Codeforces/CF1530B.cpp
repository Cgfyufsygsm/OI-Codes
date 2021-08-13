#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

int vis[22][22];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int h, w;
        scanf("%d %d", &h, &w);
        FOR(i, 1, h) FOR(j, 1, w) vis[i][j] = 0;

        FOR(j, 1, w) if (j & 1) vis[1][j] = vis[h][j] = 1;
        FOR(i, 3, h - 2) if (i & 1) vis[i][1] = vis[i][w] = 1; 

        FOR(i, 1, h) {
            FOR(j, 1, w) printf("%d", vis[i][j]);
            puts("");
        }
        puts("");
    }
    return 0;
}