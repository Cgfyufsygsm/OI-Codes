#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    int l, n; //n表示区间个数
    cin >> l >> n;
    int h[n], t[n], visited[l + 1];//visited表示用过了
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++)
        cin>>h[i]>>t[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = h[i]; j <= t[i]; j++)
        {
            visited[j] = 1;
        }
    }
    int tree = 0;
    for (int i = 0; i <= l; i++)
    {
        if (visited[i] == 0)
            tree++;
    }
    cout << tree << endl;
    return 0;
}