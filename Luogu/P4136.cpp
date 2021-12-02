#include <cstdio>

int n;

int main() {
    while (~scanf("%d", &n) && n) {
        if (n & 1) puts("Bob");
        else puts("Alice");
    }
    return 0;
}