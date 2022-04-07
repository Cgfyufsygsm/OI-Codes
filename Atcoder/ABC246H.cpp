#include <bits/stdc++.h>
#include <atcoder/modint>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using mint = atcoder::modint998244353;

template<int n, int m> struct Matrix {
    mint a[n][m];
    Matrix() {memset(a, 0, sizeof a);}
    il mint& operator()(const int &x, const int &y) {return a[x][y];}
    il const mint& operator()(const int &x, const int &y) const {return a[x][y];}
};

template<int n, int p, int m> Matrix<n, m> operator*(const Matrix<n, p> &a, const Matrix<p, m> &b) {
    Matrix<n, m> ret;
    FOR(i, 0, n - 1) FOR(j, 0, m - 1) FOR(k, 0, p - 1) ret(i, j) += a(i, k) * b(k, j);
    return ret;
}

const int maxn = 1e5 + 5;
Matrix<3, 3> A[3], t[maxn << 2];
Matrix<3, 1> F;
int n, q;
char s[maxn];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushUp(int k) {
    t[k] = t[R] * t[L];
    return;
}

void build(int i, int j, int k) {
    if (i == j) {
        if (s[i] ^ '?') t[k] = A[s[i] - '0'];
        else t[k] = A[2];
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    pushUp(k);
    return;
}

void modify(int i, int j, int k, int x, char c) {
    if (i == j) {
        if (c ^ '?') t[k] = A[c - '0'];
        else t[k] = A[2];
        return;
    }
    if (x <= M) modify(i, M, L, x, c);
    else modify(M + 1, j, R, x, c);
    pushUp(k);
    return;
}

int main() {
    A[0](0, 0) = A[0](0, 1) = A[0](0, 2) = A[0](1, 1) = A[0](2, 2) = 1;
    A[1](0, 0) = A[1](1, 0) = A[1](1, 1) = A[1](1, 2) = A[1](2, 2) = 1;
    A[2](0, 0) = A[2](0, 1) = A[2](0, 2) = A[2](1, 0) = A[2](1, 1) = A[2](1, 2) = A[2](2, 2) = 1;
    F(2, 0) = 1;
    cin >> n >> q;
    cin >> (s + 1);
    build(1, n, 1);
    while (q--) {
        int x; char c; cin >> x >> c;
        modify(1, n, 1, x, c);
        cout << (t[1](0, 2) + t[1](1, 2)).val() << endl;
    }
    return 0;
}