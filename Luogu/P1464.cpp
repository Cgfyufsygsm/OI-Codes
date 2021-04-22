#include <bits/stdc++.h>
using namespace std;

#define X(x, y, z) (X[x][y][z] ? X[x][y][z] : X[x][y][z] = w(x, y, z))

int a = 1, b = 1, c = 1;
int X[21][21][21];

int w(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
        return 1;
    if (a > 20 || b > 20 || c > 20)
        return X(20, 20, 20);
    if (a < b && b < c)
        return X(a, b, c - 1) + X(a, b - 1, c - 1) - X(a, b - 1, c);
    return X(a - 1, b, c) + X(a - 1, b - 1, c) + X(a - 1, b, c - 1) - X(a - 1, b - 1, c - 1);
}

int main()
{
    while (true)
    {
        cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1)
            break;
        cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << endl;
    }
    return 0;
}