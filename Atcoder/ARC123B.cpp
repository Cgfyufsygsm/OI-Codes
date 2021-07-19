#include <cstdio>
#include <cctype>
#include <queue>
#include <functional>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

const int maxn = 1e5 + 5;

int n, ans;
std::priority_queue<int, std::vector<int>, std::greater<int> > a, b, c;

int main() {
    n = read();
    FOR(i, 1, n) a.push(read());
    FOR(i, 1, n) b.push(read());
    FOR(i, 1, n) c.push(read());
    FOR(i, 1, n) {
        if (a.empty() || b.empty() || c.empty()) break;
        int now = a.top(); a.pop();
        while (!b.empty() && b.top() <= now) b.pop();
        if (!b.empty()) now = b.top(), b.pop();
        else break;
        while (!c.empty() && c.top() <= now) c.pop();
        if (!c.empty()) c.pop(), ++ans;
        else break;
    }
    printf("%d\n", ans);
    return 0;
}