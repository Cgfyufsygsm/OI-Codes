#include <cstdio>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

typedef vector<int> bigint;
bigint _minus(bigint, bigint);
bigint _times(bigint, bigint);
void div2(bigint&);
void print(bigint);
inline bool isodd(bigint&);

bigint _minus(bigint a, bigint b)
{
    for(int i=0;i<b.size();i++)
    {
        a[i]=a[i]-b[i];
        if(a[i]<0)
        {
            a[i+1]--;
            a[i]+=10;
        }
    }
    for(int i=b.size();i<a.size();i++)
    {
        if(a[i]<0)
            a[i+1]--,a[i]+=10;
    }
    for(int i=a.size()-1;i>0;i--)
    {
        if(a[i])
            break;
        if(!a[i])
            a.pop_back();
    }
    return a;
}

bigint _times(bigint a, bigint b)
{
    bigint ans;
    int la=a.size(),lb=b.size();
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
    return ans;
}

void div2(bigint &a)
{
    for(int i=a.size()-1;i>=0;i--)
    {
        if(a[i]&1)
            a[i-1]+=10;
        a[i]/=2;
    }
    if(!a.back())
        a.pop_back();
}

bigint read()
{
    bigint ans;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
    {
        ans.push_back(c-'0');
        c=getchar();
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

void print(bigint a)
{
    for(int i=a.size()-1;i>=0;i--)
        printf("%d",a[i]);
    printf("\n");
    return;
}

inline bool isodd(bigint &a)
{
    return a.front()&1;
}

bool cmp(bigint a, bigint b)//return a>b
{
    if(a.size()>b.size())
        return true;
    else if(a.size()<b.size())
        return false;
    else
    {
        for(int i=a.size()-1;i>=0;i--)
            if(a[i]>b[i])
                return true;
            else if(a[i]!=b[i])
                return false;
    }
    return false;
}

int main()
{
    bigint a=read(),b=read();
    bigint tag={1},two={2};
    while(a!=b)
    {
        if(!isodd(a) && !isodd(b))
        {
            div2(a);
            div2(b);
            tag=_times(tag,two);
        }
        else if(!isodd(a))
            div2(a);
        else if(!isodd(b))
            div2(b);
        else
        {
            if(cmp(a,b))
                a=_minus(a,b);
            else
                b=_minus(b,a);
        }
    }
    print(_times(a,tag));
    return 0;
}