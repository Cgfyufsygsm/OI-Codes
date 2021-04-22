#include <cstdio>
#include <cstring>

typedef long long ll;
template<typename T> void swap(T &a,T &b)
{
    T t=a;
    a=b;
    b=t;
    return;
}

struct bigint
{
    ll vec[1500];
    bool sym;
    bool operator<(const bigint b)const
    {
        if(vec[0]==b.vec[0])
            return vec[vec[0]]<b.vec[vec[0]];
        return vec[0]<b.vec[0];
    }
    bool operator>(const bigint b)const
    {
        if(vec[0]==b.vec[0])
            return vec[vec[0]]>b.vec[vec[0]];
        return vec[0]>b.vec[0];
    }
}a,b,c;

inline ll max(ll a,ll b)
{
    return a>b?a:b;
}

char s[10100];
ll powten[10];

void init(bigint &x)
{
    scanf("%s",s+1);
    int l=strlen(s+1);
    for(int i=1;i<=l;i++)
        s[i]-='0';
    for(int i=l,j=1;i>=1;i-=8,j++)
        for(int k=0;k<8 && i-k>0;k++)
            x.vec[j]+=powten[k]*s[i-k],x.vec[0]=max(x.vec[0],j);
    x.sym=1;
    return;
}

void add(bigint x,bigint y,bigint &ans)
{
    ans.sym=1;
    int ad=0;
    for(int i=1;i<=max(x.vec[0],y.vec[0]);i++)
    {
        ans.vec[i]=x.vec[i]+y.vec[i]+ad;
        ad=ans.vec[i]/powten[8];
        ans.vec[i]%=powten[8];
        ans.vec[0]=i;
    }
    if(ad)
        ans.vec[++ans.vec[0]]=ad;
    
    return;
}

void minus(bigint x,bigint y,bigint &ans)
{
    if(x<y)
        swap(x,y),ans.sym=0;
    else
        ans.sym=1;
    int ad=0;
    for(int i=1;i<=max(x.vec[0],y.vec[0]);i++)
    {
        ans.vec[i]=x.vec[i]-y.vec[i]-ad;
        if(ans.vec[i]<0)
            ans.vec[i]+=powten[8],ad=1;
        else ad=0;
        ans.vec[0]=i;
    }
    for(int i=ans.vec[0];i>=1;i--,ans.vec[0]--)
    {
        if(ans.vec[i])
            break;
    }
    return;
}

void mul(bigint x,bigint y,bigint &ans)
{
    ans.sym=1;
    for(int i=1;i<=x.vec[0];i++)
        for(int j=1;j<=y.vec[0];j++)
        {
            ans.vec[i+j-1]+=a.vec[i]*b.vec[j];
            ans.vec[i+j]+=ans.vec[i+j-1]/powten[8];
            ans.vec[i+j-1]%=powten[8];
            ans.vec[0]=i+j-1;
        }
    if(ans.vec[ans.vec[0]+1])
        ans.vec[0]++;
    for(int i=ans.vec[0];i>=1;i--,ans.vec[0]--)
    {
        if(ans.vec[i])
            break;
    }
    return;
}

void print(bigint x)
{
    if(!x.sym)
        putchar('-'); 
    printf("%lld",x.vec[x.vec[0]]);
    for(int i=x.vec[0]-1;i>=1;i--)
        printf("%08lld",x.vec[i]);
    return;
}

int main()
{
    powten[0]=1;
    for(int i=1;i<=8;i++)
        powten[i]=10*powten[i-1];
    init(a);init(b);
    mul(a,b,c);
    print(c);
    return 0;
}