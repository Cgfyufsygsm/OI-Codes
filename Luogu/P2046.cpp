#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 3e5 + 5;
int n;
struct Edge {
    int to, nxt, w;
} e[maxn * 10];
int head[maxn], cnte;
int id[505][505], S, T;

void add(int u, int v, int w) {
    e[++cnte] = {v, head[u], w};
    head[u] = cnte;
    return;
}

int dis[maxn], vis[maxn];

void Dijkstra() {
    memset(dis, 0x3f, sizeof dis);
    dis[S] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, S});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int &v = e[i].to, &w = e[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
    return;
}

int main() {
    cin >> n; ++n;
    FOR(i, 1, n) FOR(j, 1, n) id[i][j] = (i - 1) * n + j;
    S = n * n + 1, T = S + 1;
    FOR(i, 1, n) FOR(j, 1, n - 1) {
        int w; cin >> w;
        if (i == 1) add(S, id[i][j], w);
        else if (i == n) add(id[i - 1][j], T, w);
        else add(id[i - 1][j], id[i][j], w);
    }
    FOR(i, 1, n - 1) FOR(j, 1, n) {
        int w; cin >> w;
        if (j == 1) add(id[i][j], T, w);
        else if (j == n) add(S, id[i][j - 1], w);
        else add(id[i][j], id[i][j - 1], w);
    }
    FOR(i, 1, n) FOR(j, 1, n - 1) {
        int w; cin >> w;
        if (i == 1) add(id[i][j], S, w);
        else if (i == n) add(T, id[i - 1][j], w);
        else add(id[i][j], id[i - 1][j], w);
    }
    FOR(i, 1, n - 1) FOR(j, 1, n) {
        int w; cin >> w;
        if (j == 1) add(T, id[i][j], w);
        else if (j == n) add(id[i][j - 1], S, w);
        else add(id[i][j - 1], id[i][j], w);
    }
    Dijkstra();
    cout << dis[T] << endl;
    return 0;
}