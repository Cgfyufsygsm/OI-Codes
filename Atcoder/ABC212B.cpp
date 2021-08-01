#include <cstdio>

char s[10];

int main() {
    scanf("%s", s + 1);
    if (s[1] == s[2] && s[2] == s[3] && s[3] == s[4]) return puts("Weak"), 0;
    bool flag = 1;
    for (int i = 1; i <= 3; ++i) {
        if (s[i + 1] == s[i] + 1 || (s[i + 1] == '0' && s[i] == '9'));
        else flag = 0;
    }
    return puts(!flag ? "Strong" : "Weak"), 0;
}