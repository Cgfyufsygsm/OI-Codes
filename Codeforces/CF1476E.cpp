#include <iostream>
#include <cstring>
#include <queue>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e5 + 5;
int n, m, k, mt[maxn];

int trie[1000005][27], end[1000005], tot = 1;

void insert(char *s, int i)
{
    int len = strlen(s), p = 1;
    FOR(i, 0, len - 1)
    {
        int ch = s[i] - 'a';
        if (s[i] == '_')
            ch = 26;
        if (trie[p][ch] == 0)
            trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    end[p] = i;
}

void search(int len, int now, char *s, int p, std::vector<int> &S)
{
    int ch = s[now] - 'a';
    if (trie[p][ch])
        search(len, now + 1, s, trie[p][ch], S);
    if (trie[p][26])
        search(len, now + 1, s, trie[p][26], S);
    if (now == len)
        if (end[p])
            S.push_back(end[p]);
}

std::vector<int> mat;
std::vector<int> G[maxn];
std::vector<int> res;
std::queue<int> q;
int ind[maxn];

void add(int u, int v)
{
    G[u].push_back(v);
    ++ind[v];
    return;
}

int main()
{
    std::cin >> n >> m >> k;
    char str[5];
    FOR(i, 1, n)
    {
        std::cin >> str;
        insert(str, i);
    }
    FOR(i, 1, m)
    {
        std::cin >> str >> mt[i];
        mat.clear();
        search(strlen(str), 0, str, 1, mat);
        bool flag = 0;
        for (auto j : mat)
        {
            flag |= (j == mt[i]);
            if (j != mt[i])
                add(mt[i], j);
        }
        if (!flag)
        {
            std::cout << "NO\n";
            return 0;
        }
    }
    FOR(i, 1, n)
        if (!ind[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        res.push_back(u);
        for (auto v : G[u])
        {
            if (!--ind[v])
                q.push(v);
        }
    }
    if (res.size() != n)
    {
        std::cout << "NO\n";
        return 0;
    }
    else
    {
        std::cout << "YES\n";
        for (auto i : res) std::cout << i << ' ';
    }
    return 0;
}