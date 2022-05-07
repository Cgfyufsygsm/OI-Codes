#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define il inline

using namespace std;

int totMacro, alphabet[300], Sigma; // store the number of macro
string content[1005];

struct Node {
    int ch[65], end, size;
} t[600005];
int tot;

void insert(string s, int id) {
    int u = 0;
    for (auto& ch : s) {
        int c = alphabet[(int)ch];
        if (!t[u].ch[c]) t[u].ch[c] = ++tot;
        ++t[u].size;
        u = t[u].ch[c];
    }
    t[u].end = id;
    return;
}

void addMacro(const string &s) {
    int len = 0;
    string name;
    FOR(i, 0, (int)s.size() - 1) {
        if (!isspace(s[i])) ++len, name.push_back(s[i]);
        else break;
    }
    string &_content = content[++totMacro];
    insert(name, totMacro);
    _content = s.substr(len + 1);
    return;
}

void delMacro(const string& s) {
    int u = 0;
    for (auto& ch : s) {
        int c = alphabet[(int)ch];
        --t[u].size;
        int uu = u;
        u = t[u].ch[c];
        if (!t[uu].size) t[uu].ch[c] = 0;
    }
    t[u].end = 0;
    return;
}

bool vis[1005];

int match(string s) {
    int u = 0;
    for (auto& ch : s) {
        int c = alphabet[(int)ch];
        u = t[u].ch[c];
        if (!u) return 0;
    }
    return t[u].end;
}

string work(string s) {
    string res;
    int id, pos = 0;
    while (pos < (int)s.length()) {
        string tmp;
        while (pos < (int)s.length() && !alphabet[(int)s[pos]]) res.push_back(s[pos++]);
        while (pos < (int)s.length() && alphabet[(int)s[pos]]) tmp.push_back(s[pos++]);
        if ((id = match(tmp)) && !vis[id]) vis[id] = 1, res.append(work(content[id])), vis[id] = 0;
        else res.append(tmp);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    FOR(i, 'a', 'z') alphabet[i] = ++Sigma;
    FOR(i, 'A', 'Z') alphabet[i] = ++Sigma;
    FOR(i, '0', '9') alphabet[i] = ++Sigma;
    alphabet['_'] = ++Sigma;
    string num;
    getline(cin, num);
    int n = 0;
    for (auto& c : num) n = 10 * n + (c - '0');
    FOR(line, 1, n) {
        string s;
        getline(cin, s);
        if (!s.empty() && s[0] == '#') {
            if (s[1] == 'd') addMacro(s.substr(8));
            else if (s[1] == 'u') delMacro(s.substr(7));
            cout << endl;
        } else {
            cout << work(s) << endl;
        }
    }
    return 0;
}