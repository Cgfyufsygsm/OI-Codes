#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#include <functional>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

il int min(int a, int b) {return a < b ? a : b;}
il int max(int a, int b) {return a > b ? a : b;}

int main() {
    int T, a, b, c, m;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d", &a, &b, &c, &m);
        int mx = (a ? a - 1 : 0) + (b ? b - 1 : 0) + (c ? c - 1 : 0);
        std::vector<int> v;
        if (a) v.push_back(a);
        if (b) v.push_back(b);
        if (c) v.push_back(c);
        std::sort(v.begin(), v.end(), std::greater<int>());
        if (m < v[0] - v[1] - v[2] - 1 || m > mx) puts("NO");
        else puts("YES");
    }
    return 0;
}