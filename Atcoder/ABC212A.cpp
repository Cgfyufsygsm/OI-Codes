#include <cstdio>

int a, b;

int main() {
    scanf("%d %d", &a, &b);
    if (0 < a && b == 0) puts("Gold");
    if (a == 0 && 0 < b) puts("Silver");
    if (0 < a && 0 < b) puts("Alloy");
    return 0;
}