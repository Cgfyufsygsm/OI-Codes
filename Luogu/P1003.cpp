#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[n+1], b[n+1], j[n+1], k[n+1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i] >> j[i] >> k[i];
    }
    int x, y;
    cin >> x >> y;
    int num=-1;
    for (int i = 1; i <= n; i++)
    {
        int endx,endy;
        endx=a[i]+j[i];
        endy=b[i]+k[i];
        if(x>=a[i]&&x<=endx&&y>=b[i]&&y<=endy)
            num=i;
    }
    cout<<num<<endl;
    return 0;
}