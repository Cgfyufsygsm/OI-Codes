#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

char s[11];
int ans;

void dfs(int cur, int win1, int win2, int rem1, int rem2) {
    if (cur > 10) return;
    if (win1 + rem1 < win2 || win2 + rem2 < win1) {
        ans = min(ans, cur - 1);
        return;
    }
    if (s[cur] == '1') dfs(cur + 1, win1 + (cur & 1), win2 + !(cur & 1), rem1 - (cur & 1), rem2 - !(cur & 1));
    else if (s[cur] == '0') dfs(cur + 1, win1, win2, rem1 - (cur & 1), rem2 - !(cur & 1));
    else if (s[cur] == '?') dfs(cur + 1, win1 + (cur & 1), win2 + !(cur & 1), rem1 - (cur & 1), rem2 - !(cur & 1)), dfs(cur + 1, win1, win2, rem1 - (cur & 1), rem2 - !(cur & 1));
    return;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        ans = 10;
        dfs(1, 0, 0, 5, 5);
        printf("%d\n", ans);
    }
    return 0;
}