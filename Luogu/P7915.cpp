#include <cstdio>
#include <cctype>
#include <deque>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
template<typename T> void read(T &n) {
    int x = 0; n = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        n = n * 10 + c - '0', c = getchar();
    n = x ? -n : n;
}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e6 + 5;
int a[maxn], n;
char ans[maxn];
std::deque<int> q1, q2;

bool solve() {
    int cnt = 1;
    while (!q1.empty() || !q2.empty()) {
        ++cnt;
        if (q1.size() >= 2 && q1.back() == q1.front()) {
            ans[cnt] = 'L', ans[2 * n - cnt + 1] = 'L';
            q1.pop_back(), q1.pop_front();
        } else if (!q1.empty() && !q2.empty() && q1.back() == q2.front()) {
            ans[cnt] = 'L', ans[2 * n - cnt + 1] = 'R';
            q1.pop_back(), q2.pop_front();
        } else if (!q1.empty() && !q2.empty() && q2.back() == q1.front()) {
            ans[cnt] = 'R', ans[2 * n - cnt + 1] = 'L';
            q1.pop_front(), q2.pop_back();
        } else if (q2.size() >= 2 && q2.back() == q2.front()) {
            ans[cnt] = 'R', ans[2 * n - cnt + 1] = 'R';
            q2.pop_back(), q2.pop_front();
        } else return false;
    }
    return true;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, 2 * n) read(a[i]);
        bool flag = 0;
        ans[1] = ans[2 * n] = 'L';
        int p = 0;
        q1.clear(), q2.clear();
        FOR(i, 2, 2 * n) {
            if (a[i] == a[1]) p = i;
            else if (p) q2.push_back(a[i]);
            else q1.push_front(a[i]);
        }
        if (solve()) flag = 1;
        else {
            q1.clear(), q2.clear();
            ans[1] = 'R', ans[2 * n] = 'L';
            p = 0;
            FOR(i, 1, 2 * n - 1) {
                if (a[i] == a[2 * n]) p = i;
                else if (p) q2.push_back(a[i]);
                else q1.push_front(a[i]);
            }
            if (solve()) flag = 1;
        }
        if (flag) FOR(i, 1, 2 * n) putchar(ans[i]);
        else printf("-1");
        puts("");
    }
    return 0;
}