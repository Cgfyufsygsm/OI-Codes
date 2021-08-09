#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define VEC(i, v) for (int i = 0; i < v.size(); ++i)

const int maxn = 505;
int h, w;
char s[maxn][maxn];

int dis[maxn][maxn];

struct node {
    int x, y, dis;
};

const int fx[] = {1, -1, 0, 0};
const int fy[] = {0, 0, 1, -1};

il int abs(int x) {return x >= 0 ? x : -x;}
il bool check(int x, int y) {return x > 0 && x <= h && y > 0 && y <= w;}

int main() {
    scanf("%d %d", &h, &w);
    FOR(i, 1, h) scanf("%s", s[i] + 1);
    memset(dis, 0x3f, sizeof dis);
    dis[1][1] = 0;
    std::deque<node> q;
    q.push_back((node){1, 1, 0});
    while (!q.empty()) {
        auto now = q.front(); q.pop_front();
        if (now.x == h && now.y == w) break;
        FOR(k, 0, 3) {
            int tx = now.x + fx[k], ty = now.y + fy[k];
            if (!check(tx, ty)) continue;
            if (s[tx][ty] == '#' || now.dis >= dis[tx][ty]) continue;
            dis[tx][ty] = now.dis;
            q.push_front((node){tx, ty, now.dis});
        }
        FOR(fx, -2, 2)
            FOR(fy, -2, 2) {
                if (abs(fx) + abs(fy) > 3) continue;
                int tx = now.x + fx, ty = now.y + fy;
                if (!check(tx, ty)) continue;
                if (dis[tx][ty] <= now.dis + 1) continue;
                dis[tx][ty] = now.dis + 1;
                q.push_back((node){tx, ty, now.dis + 1});
            }
    }
    printf("%d\n", dis[h][w]);
    return 0;
}