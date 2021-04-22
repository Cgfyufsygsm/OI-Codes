#include <iostream>
using namespace std;


int main()
{
    int n,l;
    cin>>l>>n;
    int mint=0,maxt=0;
    for(int i=1;i<=n;i++)
    {
        int d;
        cin>>d;
        mint=max(min(d,l-d+1),mint);
        maxt=max(max(d,l-d+1),maxt);
    }
    cout<<mint<<' '<<maxt<<endl;
    return 0;
}