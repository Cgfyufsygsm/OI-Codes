#include <cstdio>
#include <cstring>

char s[100005];

int main()
{
    scanf("%s", s + 1);
    for (int i = strlen(s + 1) + 1; i >= 1; --i)
    {
        if (s[i] == '0') putchar('0');
        else if (s[i] == '1') putchar('1');
        else if (s[i] == '6') putchar('9');
        else if (s[i] == '8') putchar('8');
        else if (s[i] == '9') putchar('6');
    }
    return 0;
}