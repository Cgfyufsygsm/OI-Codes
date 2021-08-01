#include <cstdio>
#include <cmath>

int n1, n2, n12;

int main() {
    scanf("%d %d %d", &n1, &n2, &n12);
    printf("%d\n", (int)floor((n1 + 1.0) * (n2 + 1.0) / (n12 + 1.0) - 1));
    return 0;
}