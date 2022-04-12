#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 1 << 20 | 5;
int n, k, vis[maxn];
vector<int> a, b;

void dfs(int x) {
    a.push_back(x); vis[x] = 1;
    if (a.size() == (1 << n)) {
        puts("Yes");
        for (auto &x : a)
            cout << x << " "; exit(0);
    }
    for (auto &c : b) if (!vis[c ^ x]) dfs(c ^ x);
    return;
}

int main() {
    cin >> n >> k;
    if (k % 2 == 0) return puts("No"), 0;
    FOR(i, 0, (1 << n) - 1) if (__builtin_popcount(i) == k) b.push_back(i);
    dfs(0);
    return puts("No"), 0;
}