#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    if (n <= 125) printf("4\n");
    else if (n <= 211) printf("6\n");
    else printf("8\n");
    return 0;
}