#include <cstdio>
#include <cctype>
#include <queue>
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

const int maxn = 3005;
int n, a[maxn];
long long ans;
std::priority_queue<int> q;

int main() {
    n = read();
    FOR(i, 1, n) a[i] = read() - i;
    FOR(i, 1, n) {
        q.push(a[i]);
        if (!q.empty() && q.top() > a[i]) {
            ans += q.top() - a[i];
            q.pop();
            q.push(a[i]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}