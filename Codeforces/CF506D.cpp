#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define szof(a) ((int) (a).size())

using namespace std;
using namespace YangTY::fastIO;
using pii = pair<int, int>;
const int maxn = 1e5 + 5, B = 316;
int n, m;
vector<pii> e[maxn];

struct Query {
    int u, v, ans;
} q[maxn];

struct UnionFind {
    int fa[maxn];
    int find(int u) {return u == fa[u] ? u : fa[u] = find(fa[u]);}
    il void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u != v) fa[u] = v;
        return;
    }
    il int query(int u, int v) {return find(u) == find(v);}
} ufs;
int tot;

struct myhash {
    il long long operator()(const pii &a) const {
        return (a.first << 17ll) + a.second;
    }
};

unordered_map<pii, int, myhash> mp, col;

int main() {
    is >> n >> m;
    FOR(i, 1, m) {
        int u, v, c;
        is >> u >> v >> c;
        if (u > v) swap(u, v);
        e[c].emplace_back(u, v);
    }
    int Q; is >> Q;
    FOR(i, 1, Q) {
        is >> q[i].u >> q[i].v;
        if (q[i].u > q[i].v) swap(q[i].u, q[i].v);
    }
    FOR(i, 1, n) ufs.fa[i] = i;
    FOR(i, 1, m) {
        if (e[i].size() >= B) {
            for (auto &p : e[i])
                ufs.merge(p.first, p.second);
            FOR(j, 1, Q) {
                if (col[{q[j].u, q[j].v}] == i) ++q[j].ans;
                else if (ufs.query(q[j].u, q[j].v)) ++q[j].ans, col[{q[j].u, q[j].v}] = i;
            }
        } else {
            vector<int> node;
            for (auto &p : e[i])
                ufs.merge(p.first, p.second), node.emplace_back(p.first), node.emplace_back(p.second);
            sort(node.begin(), node.end());
            node.erase(unique(node.begin(), node.end()), node.end());
            FOR(i, 0, szof(node) - 1) FOR(j, i + 1, szof(node) - 1)
                if (ufs.query(node[i], node[j])) ++mp[{node[i], node[j]}];
        }
        for (auto &p : e[i]) ufs.fa[p.first] = p.first, ufs.fa[p.second] = p.second;
    }
    FOR(i, 1, Q) os << mp[{q[i].u, q[i].v}] + q[i].ans << '\n';
    return 0;
}