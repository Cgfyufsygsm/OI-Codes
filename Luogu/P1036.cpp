#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

int n, k, cnt, x[21];

bool is_prime(int n)
{
    if (n == 2)
        return true;
    if (n % 2 == 0 || n == 1)
        return false;
    else
    {
        for (int i = 3; i <= sqrt(n) + 1; i += 2)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
    }
    return true;
}

void dfs(int i, int nums, int sum)
{
    if (nums == k)
    {
        if (is_prime(sum))
            cnt++;
    }
    else if (i <= n)
    {
        dfs(i + 1, nums, sum);
        dfs(i + 1, nums + 1, sum + x[i]);
    }
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    dfs(1, 0, 0);
    cout << cnt << endl;
    return 0;
}