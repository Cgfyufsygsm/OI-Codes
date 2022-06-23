#include <cstdio>
#include <cctype>

const int mod = 999292927;

int main() {
    char c = getchar();
    int ans = 0;
    while (isdigit(c)) {
        ans = (10ll * ans + c - '0') % mod;
        c = getchar();
    }
    printf("%d\n", ans);
    return 0;
}