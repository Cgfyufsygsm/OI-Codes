#include <stdio.h>
int main()
{
    for (int a = 1; a <= 3; a++)
    {
        for (int b = 1; b <= 9; b++)
        {
            for (int c = 1; c <= 9; c++)
            {
                for (int d = 1; d <= 9; d++)
                {
                    for (int e = 1; e <= 9; e++)
                    {
                        for (int f = 1; f <= 9; f++)
                        {
                            for (int g = 1; g <= 9; g++)
                            {
                                for (int h = 1; h <= 9; h++)
                                {
                                    for (int i = 1; i <= 9; i++)
                                    {
                                        if (a == b || a == c || a == d || a == e || a == f || a == g || a == h || a == i || b == c || b == d || b == e || b == f || b == g || b == h || b == i || c == d || c == e || c == f || c == g || c == h || c == i || d == e || d == f || d == g || d == h || d == i || e == f || e == g || e == h || e == i || f == g || f == h || f == i || g == h || g == i || h == i)
                                            continue;
                                        int abc = 100 * a + 10 * b + c;
                                        int def = 100 * d + 10 * e + f;
                                        int ghi = 100 * g + 10 * h + i;
                                        if (2 * abc == def && 3 * abc == ghi)
                                            printf("%d %d %d\n", abc, def, ghi);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}