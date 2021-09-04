#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define il inline

typedef long long ll;

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

template<int row, int col>
struct Matrix {
    ll ele[row][col];
    Matrix() {memset(ele, 0xcf, sizeof ele);}
    il ll* operator[](int a) {return ele[a];}
};

template<int m, int n, int p> Matrix<m, p> operator*(Matrix<m, n> a, Matrix<n, p> b) {
    Matrix<m, p> ret;
    FOR(k, 0, n - 1) {
        FOR(i, 0, m - 1) {
            FOR(j, 0, p - 1) {
                ret[i][j] = max(ret[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return ret;
}

template<int n> Matrix<n, n> qPow(Matrix<n, n> mat, ll exp) {
    Matrix<n, n> ret;
    FOR(i, 0, n - 1) ret.ele[i][i] = 0;
    for (; exp; exp >>= 1, mat = mat * mat)
        if (exp & 1) ret = ret * mat;
    return ret;
}

struct node {
    int ch[26], fail;
    ll val;
} t[205];

int tot;

void insert(char *s, ll val) {
    int u = 0, len = strlen(s + 1);
    FOR(i, 1, len) {
        int c = s[i] - 'a';
        if (!t[u].ch[c]) t[u].ch[c] = ++tot;
        u = t[u].ch[c];
    }
    t[u].val += val;
    return;
}

void build() {
    static int q[205], qhead = 1, qtail = 0;
    FOR(c, 0, 25) if (t[0].ch[c]) q[++qtail] = t[0].ch[c];
    while (qhead <= qtail) {
        int u = q[qhead++];
        t[u].val += t[t[u].fail].val;
        FOR(c, 0, 25)
            if (t[u].ch[c]) t[t[u].ch[c]].fail = t[t[u].fail].ch[c], q[++qtail] = t[u].ch[c];
            else t[u].ch[c] = t[t[u].fail].ch[c];
    }
    return;
}

int n;
char str[205];
ll l, v0[205];

int main() {
    scanf("%d %lld", &n, &l);
    FOR(i, 1, n) scanf("%lld", v0 + i);
    FOR(i, 1, n) {
        scanf("%s", str + 1);
        insert(str, v0[i]);
    }
    build();
    Matrix<205, 205> trans;
    Matrix<205, 1> v;
    v[0][0] = 0;
    FOR(u, 0, tot)
        FOR(c, 0, 25)
            trans[t[u].ch[c]][u] = max(trans[t[u].ch[c]][u], t[t[u].ch[c]].val);
    v = qPow(trans, l) * v;
    ll ans = 0;
    FOR(i, 0, tot) ans = max(ans, v[i][0]);
    printf("%lld\n", ans);
    return 0;
}