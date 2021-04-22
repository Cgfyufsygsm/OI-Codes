#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

bool is_prime(unsigned n)
{
    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

bool is_palindrome(unsigned n)
{
    if (n < 10)
        return true;
    if ((n > 9 && n < 100) && n / 10 == n % 10)
        return true;
    if ((n > 9 && n < 100) && n / 10 != n % 10)
        return false;
    char str[10];
    sprintf(str, "%d", n);
    short end;
    for (int i = 0; i < 10; i++)
    {
        if (str[i] == '\0')
        {
            end = i;
            break;
        }
    }
    for (int i = 0; i < end / 2; i++)
    {
        if (str[i] != str[end - 1 - i])
            return false;
    }
    return true;
}

bool ws(int k)
{
    if (k >= 10 && k < 100 && k != 11 || k >= 1000 && k < 10000)
        return false;
    if (k >= 100000 && k < 1000000 || k >= 10000000 && k < 100000000)
        return false;
    return true;
}

int main()
{
    unsigned a, b;
    scanf("%u%u", &a, &b);
    if (a % 2 == 0)
        a++;
    if (b % 2 == 0)
        b--;
    for (unsigned i = a; i <= b; i += 2)
    {
        if(!ws(i))
            continue;
        if (!is_palindrome(i))
            continue;
        else if (!is_prime(i))
            continue;
        else
            printf("%u\n", i);
    }
    return 0;
}