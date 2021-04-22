#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef vector<int> bigint;

bigint operator*(bigint a, bigint b)
{
    bigint ans;
    int la=a.size()>500?500:a.size(),lb=b.size()>500?500:b.size();
    for(int i=0;i<la+lb;i++)
        ans.push_back(0);
    for(int i=0;i<lb;i++)
    {
        for(int j=0;j<la;j++)
        {
            ans[i+j]+=a[j]*b[i];
            if(ans[i+j]>=10)
            {
                ans[i+j+1]+=ans[i+j]/10;
                ans[i+j]%=10;
            }
        }
    }
    for(int i=ans.size()-1;i>0;i--)
    {
        if(ans[i])
            break;
        else
            ans.pop_back();
    }
    if(ans.size()>500) 
        ans.resize(500);
    return ans;
}

bigint ksm(int p)
{
    bigint base={2};
    bigint ans={1};
    while(p)
    {
        if(p&1)
            ans=ans*base;
        base=base*base;
        p>>=1;
    }
    ans.resize(500,0);
    return ans;
}

void print(bigint a)
{
    a[0]--;
    reverse(a.begin(),a.end());
    int j=1;
    for(auto i:a)
    {
        printf("%d",i);
        if(j%50==0)
            printf("\n");
        j++;
    }
    return;
}

int main()
{
    int p;
    scanf("%d",&p);
    printf("%lld\n",(long long)(p*(double)log10((double)2.0)+1));
    bigint ans=ksm(p);
    print(ans);
    return 0;
}