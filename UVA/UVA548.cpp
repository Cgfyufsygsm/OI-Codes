#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int maxn=1e4+5;
int in_o[maxn],post_o[maxn],lson[maxn],rson[maxn],n;

void read(string s,int *a)
{
    stringstream ss(s);
    n=0;
    int x;
    while(ss>>x)
        a[n++]=x;
    return;
}


int ans,ans_sum;

int build(int l1,int r1,int l2,int r2,int sum)
{
    if(l1>r1)
        return 0;
    int root=post_o[r2];
    sum+=root;
    int p=l1;
    while(in_o[p]!=root)
        p++;
    int cnt=p-l1;
    lson[root]=build(l1,p-1,l2,l2+cnt-1,sum);
    rson[root]=build(p+1,r1,l2+cnt,r2-1,sum);
    if(!lson[root] && !rson[root])
        if(sum<ans_sum || (sum==ans_sum && root<ans))
            ans_sum=sum,ans=root;
    return root;
}


int main()
{
    string in,post;
    while(getline(cin,in) && getline(cin,post))
    {
        read(in,in_o);
        read(post,post_o);
        ans_sum=0x7f7f7f7f;
        build(0,n-1,0,n-1,0);
        cout<<ans<<endl;
    }
    return 0;
}