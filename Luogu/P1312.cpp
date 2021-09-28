#include <cstdio>
#include <cctype>
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
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il void swap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

struct State {
    int a[5][7];

    State() {
        FOR(x, 0, 4) FOR(y, 0, 6) a[x][y] = 0;
    }

    bool ok() {
        int sum = 0;
        FOR(x, 0, 4) sum += a[x][0];
        return !sum;
    }

    bool fall() {
        bool ret = 0;
        FOR(x, 0, 4) {
            int top = 0;
            FOR(y, 0, 6) if (a[x][y]) ret |= (top != y), a[x][top++] = a[x][y];
            while (top <= 6) a[x][top++] = 0;
        }
        return ret;
    }

    bool del() {
        bool ret = 0;
        bool vis[5][7];
        FOR(x, 0, 4) FOR(y, 0, 6) vis[x][y] = 0;
        FOR(x, 0, 4) FOR(y, 2, 6) if (a[x][y] && a[x][y - 2] == a[x][y - 1] && a[x][y - 1] == a[x][y]) vis[x][y - 2] = vis[x][y - 1] = vis[x][y] = ret = 1;
        FOR(y, 0, 6) FOR(x, 2, 4) if (a[x][y] && a[x - 2][y] == a[x - 1][y] && a[x - 1][y] == a[x][y]) vis[x - 2][y] = vis[x - 1][y] = vis[x][y] = ret = 1;
        FOR(x, 0, 4) FOR(y, 0, 6) if (vis[x][y]) a[x][y] = 0;
        return ret;
    }

    void fix() {
        while (true) {
            bool flag = 0;
            flag |= fall();
            flag |= del();
            if (!flag) break;
        }
        return;
    }
} init;

struct Operation {
    int x, y, g;
    Operation(int a = 0, int b = 0, int c = 0) : x(a), y(b), g(c) {}
} op[7];
int n;

bool dfs(State now, int step) {
    if (step == n) {
        if (now.ok()) {
            FOR(i, 1, step) print(op[i].x), putchar(' '), print(op[i].y), putchar(' '), print(op[i].g), putchar('\n');
            return true;
        } else return false;
    }
    FOR(x, 0, 4) {
        FOR(y, 0, 6) {
            if (now.a[x][y]) {
                if (x < 4) {
                    State to = now;
                    swap(to.a[x][y], to.a[x + 1][y]);
                    to.fix();
                    op[step + 1] = Operation(x, y, 1);
                    if (dfs(to, step + 1)) return true;
                }
                if (x > 0) {
                    State to = now;
                    if (!to.a[x - 1][y]) {
                        swap(to.a[x][y], to.a[x - 1][y]);
                        to.fix();
                        op[step + 1] = Operation(x, y, -1);
                        if (dfs(to, step + 1)) return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    read(n);
    FOR(x, 0, 4) {
        FOR(y, 0, 8) {
            read(init.a[x][y]);
            if (!init.a[x][y]) break;
        }
    }
    if (!dfs(init, 0)) puts("-1");
    return output(), 0;
}