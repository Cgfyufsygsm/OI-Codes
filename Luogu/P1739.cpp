#include <iostream>
using namespace std;

int main()
{
    char a;
    int ok=0;
    for (int i = 0;; i++)
    {
        a = getchar();
        if (i == 0 && a == ')')
        {
            printf("NO");
            return 0;
        }
        if (a == '(')
            ok++;
        if (a == ')')
            ok--;
        if (ok < 0)
        {
            printf("NO");
            return 0;
        }
        if (a == '@')
        {
            if (!ok)
                printf("YES");
            else
                printf("NO");
            return 0;
        }
    }
}