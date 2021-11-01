#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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

char s[105];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        char minc = 'z' + 1;
        FOR(i, 1, n) chkmin(minc, s[i]);
        printf("%c ", minc);
        bool flag = 1;
        FOR(i, 1, n) {
            if (flag && s[i] == minc) flag = 0;
            else printf("%c", s[i]);
        }
        puts("");
    }
    return 0;
}