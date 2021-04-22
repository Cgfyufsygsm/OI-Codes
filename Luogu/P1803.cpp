#include<iostream>
#include<algorithm>
using namespace std;
struct contest
{
    int l,r;
}c[10000001];
int n;
bool cmp(contest a,contest b)
{
    return a.r<b.r;
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>c[i].l>>c[i].r;
    sort(c,c+n,cmp);
    int ans=0,end=0;
    for(int i=0;i<n;i++)
    {
        if(end<=c[i].l)
        {
            end = c[i].r;
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}