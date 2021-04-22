#include <iostream>
#include <algorithm>
using namespace std;

class people
{
public:
    int w, d, d2, c;
};

bool cmp(people a, people b)
{
    if (a.w != b.w)
        return a.w > b.w;
    else
        return a.d < b.d;
}

int E[10];

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < 10; i++)
        cin >> E[i];
    people x[n];
    for (int i = 0; i < n; i++)
    {
        cin >> x[i].w;
        x[i].d = i+1;
    }
    sort(x, x + n, cmp);
    //for (int i = 0; i < n; i++)
    //    cout << x[i].d << " ";
    for (int i = 0; i < n; i++)
    {
        x[i].c=i%10;
        x[i].w+=E[x[i].c];
        //cout<<x[i].w<<" ";
    }
    sort(x,x+n,cmp);
    for(int i=0;i<k;i++)
        cout<<x[i].d<<" ";
    return 0;
}