#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

int calc0[26][26], calc[26][26];
char k[105], s[1005];

int main() {
    FOR(i, 0, 25)
        FOR(j, 0, 25)
            calc0[i][j] = (i + j) % 26;
    FOR(i, 0, 25) 
        FOR(j, 0, 25)
            calc[i][calc0[i][j]] = j;
    scanf("%s", k);
    scanf("%s", s);
    int lenk = strlen(k), lens = strlen(s);
    FOR(i, 0, lenk - 1) {
        if (k[i] >= 'A' && k[i] <= 'Z') k[i] -= 'A';
        else if (k[i] >= 'a' && k[i] <= 'z') k[i] -= 'a';
    }
    FOR(i, 0, lens - 1) {
        int flag = 0;
        if (s[i] >= 'A' && s[i] <= 'Z') flag = 'A', s[i] -= 'A';
        else flag = 'a', s[i] -= 'a';
        putchar(calc[k[i % lenk]][s[i]] + flag);
    }
    return 0;
}