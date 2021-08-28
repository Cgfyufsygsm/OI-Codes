#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e7;

int read() {
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

int vis[maxn + 5], phi[maxn + 5], p[maxn + 5], cntp;

void init() {
    phi[1] = 1;
    FOR(i, 2, maxn) {
        if (!vis[i]) p[++cntp] = i, phi[i] = i - 1;
        FOR(j, 1, cntp) {
            if (i * p[j] > maxn) break;
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
    return;
}

int qpow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % p)
        if (b & 1)
            ret = 1ll * ret * a % p;
    return ret;
}

int calc(int p) {
    if (p == 1) return 0;
    return qpow(2, calc(phi[p]) + phi[p], p);
}

int main() {
    int T = read();
    init();
    while (T--) {
        int n = read();
        printf("%d\n", calc(n));
    }
    return 0;
}