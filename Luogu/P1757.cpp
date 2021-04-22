#include <cstdio>
#include <vector>
#include <utility>

std::vector<std::pair<int,int> > group[102];
int m,n,f[1005];

inline int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    scanf("%d %d",&m,&n);
    for(int i=1;i<=n;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        group[c].push_back(std::make_pair(a,b));
    }
    for(int k=0;k<102;k++)
        if(!(group[k].size()))
            continue;
        else
            for(int j=m;j>=0;j--)
                for(auto i:group[k])
                    if(j>=i.first)
                        f[j]=max(f[j],f[j-i.first]+i.second);
    printf("%d\n",f[m]);
    return 0;
}