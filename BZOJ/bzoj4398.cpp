#include <cstdio>
#include <cctype>
#include <queue>
#include <utility>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 40005, maxm = 3e5 + 5;

template<typename T> void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

int n, m;
int head[2][maxn], cnt[2], cnte1;

struct edge
{
    int to, nxt, w;
} e[2][maxm];

struct edge1
{
    int to, out, in;
} e1[maxm];

void add(int u, int v, int w, int k)
{
    e[k][++cnt[k]].to = v;
    e[k][cnt[k]].w = w;
    e[k][cnt[k]].nxt = head[k][u];
    head[k][u] = cnt[k];
    //printf("added %d to %d, %d %d\n", u, v, w, k);
    return;
}

int dijkstra(int s, int t)
{
    using namespace std;
    static int dis[maxn], vis[maxn];
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (!vis[u])
        {
            vis[u] = 1;
            FOR(k, 0, 1)
                for (int i = head[k][u]; i; i = e[k][i].nxt)
                {
                    int v = e[k][i].to, w = e[k][i].w;
                    if (dis[u] + w < dis[v])
                    {
                        dis[v] = dis[u] + w;
                        q.push(make_pair(dis[v], v));
                    }
                }
        }
    }
    return dis[t];
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, m)
    {
        int u = read(), v = read(), ta = read(), tb = read();
        if (u == 1 || v == 1)
        {
            if (v == 1)
                swap(u, v), swap(ta, tb);
            e1[++cnte1].to = v, e1[cnte1].out = ta, e1[cnte1].in = tb;
        }
        else
        {
            add(u, v, ta, 0);
            add(v, u, tb, 0);
        }
    }
    int s1 = 1, s2 = n + 1, ans = 1e9;
    for (int k = 1; k <= n; k <<= 1)
    {
        cnt[1] = 0;
        memset(head[1], 0, sizeof head[1]);
        FOR(i, 1, cnte1)
        {
            if (e1[i].to & k)
            {
                //printf("div1 %d\n", e1[i].to);
                add(s1, e1[i].to, e1[i].out, 1);
                add(e1[i].to, s1, e1[i].in, 1);
            }
            else
            {
                //printf("div2 %d\n", e1[i].to);
                add(s2, e1[i].to, e1[i].out, 1);
                add(e1[i].to, s2, e1[i].in, 1);
            }
        }
        int tmp1, tmp2;
        ans = min(ans, tmp1 = dijkstra(s1, s2));
        ans = min(ans, tmp2 = dijkstra(s2, s1));
        //printf("%d %d\n", tmp1, tmp2);
    }
    printf("%d\n", ans);
    return 0;
}