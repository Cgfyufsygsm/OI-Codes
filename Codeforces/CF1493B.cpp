#include <cstdio>
#include <cctype>

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

const int rev[10] = {0, 1, 5, -1, -1, 2, -1, -1, 8, -1};
int h, m, hh, mm;

bool check()
{
    int a = hh / 10, b = hh % 10, c = mm / 10, d = mm % 10;
    if (rev[a] >= 0 && rev[b] >= 0 && rev[c] >= 0 && rev[d] >= 0)
    {
        int rh = rev[d] * 10 + rev[c], rm = rev[b] * 10 + rev[a];
        return rh < h && rm < m;
    }
    return 0;
}

void nxt()
{
    mm = (mm + 1) % m;
    if (!mm) hh = (hh + 1) % h;
    return;
}

int main()
{
    int T = read();
    while (T--)
    {
        h = read(), m = read(), hh = read(), mm = read();
        while (!check())
            nxt();
        printf("%02d:%02d\n", hh, mm);
    }
    return 0;
}