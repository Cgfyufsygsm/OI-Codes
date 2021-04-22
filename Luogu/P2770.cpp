#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <map>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

using std::cin;
using std::cout;
using std::endl;

inline int min(int a, int b) {return a < b ? a : b;}

std::map<std::string, int> m1;
std::map<int, std::string> m2;

const int maxn = 505, maxm = 1e5 + 5, inf = 1e9;
int head[maxn], cnt = 1;
int inq[maxn], dis[maxn], flow[maxn], pre[maxn];
int n, s, t;
bool vis[maxn];

struct edge
{
    int to, nxt, w, cost;
} e[maxm];

void add(int u, int v, int w, int c)
{
    e[++cnt].to = v, e[cnt].w = w, e[cnt].cost = c, e[cnt].nxt = head[u], head[u] = cnt;
    e[++cnt].to = u, e[cnt].w = 0, e[cnt].cost = -c ,e[cnt].nxt = head[v], head[v] = cnt;
    return;
}

bool SPFA()
{
    memset(inq, 0, sizeof inq);
    memset(dis, 0xc0, sizeof dis);
    std::queue<int> q;
    q.push(s), inq[s] = 1, dis[s] = 0;
    flow[s] = inf;
    while (!q.empty())
    {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (e[i].w > 0 && e[i].cost + dis[u] > dis[v])
            {
                dis[v] = dis[u] + e[i].cost;
                flow[v] = min(flow[u], e[i].w);
                pre[v] = i;
                if (!inq[v])
                    q.push(v), inq[v] = 1;
            }
        }
    }
    return dis[t] > (int)0xc0c0c0c0;
}

void update(int &maxcost, int &maxflow)
{
    int now = t;
    while (now != s)
    {
        int i = pre[now];
        e[i].w -= flow[t];
        e[i ^ 1].w += flow[t];
        now = e[i ^ 1].to;
    }
    maxflow += flow[t];
    maxcost += flow[t] * dis[t];
    return;
}

void dfs1(int u)
{
    vis[u] = 1;
    cout << m2[u - n] << endl;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v <= n && !e[i].w)
        {
            dfs1(v + n);
            return;
        }
    }
    return;
}

void dfs2(int u)
{
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v <= n && !e[i].w && !vis[v + n])
            dfs2(v + n);
    }
    cout << m2[u - n] << endl;
    return;
}

int main()
{
    int _v;
    cin >> n >> _v;
    s = 1, t = (n << 1);
    std::string s1, s2;
    FOR(i, 1, n)
    {
        cin >> s1;
        m1[s1] = i;
        m2[i] = s1;
        if (i != 1 && i != n)
            add(i, n + i, 1, 0);
        else add(i, n + i, 2, 0);
    }
    add(s, 1, 2, 0);
    add(n * 2, t, 2, 0);
    bool flag = 0;
    FOR(i, 1, _v)
    {
        cin >> s1 >> s2;
        int u = m1[s1], v = m1[s2];
        add(u + n, v, 1, 1);
        if (u == 1 && v == n)
            flag = 1;
    }
    int maxflow = 0, maxcost = 0;
    while (SPFA())
        update(maxcost, maxflow);
    if (maxflow == 2)
    {
        cout << maxcost << endl;
        dfs1(1 + n);
        dfs2(1 + n);
    }
    else if (maxflow == 1 && flag)
    {
        cout << 2 << endl;
        cout << m2[1] << endl << m2[n] << endl << m2[1] << endl;
    }
    else cout << "No Solution!" << endl;
    return 0;
}