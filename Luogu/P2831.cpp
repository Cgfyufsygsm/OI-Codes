#include <cstdio>
#include <cmath>
#include <cstring>
#define EPS 1e-6
using namespace std;

struct point
{
    double x,y;
};

int n,m,para[200],f[1<<18],cnt;

inline bool ison(point p,double a,double b)//判断点在不在抛物线上
{
    return fabs(a*p.x*p.x+b*p.x-p.y)<=EPS;
}

inline bool calc(point d1,point d2,double &a,double &b)//计算过(x1,y1)和(x2,y2)的抛物线表达式
{
    if(fabs(d1.x-d2.x)<EPS)
        return false;
    if(fabs(d2.y/d2.x-d1.y/d1.x)<EPS)
        return false;
    b=(d1.y*d2.x*d2.x/d1.x/d1.x-d2.y)/((d2.x*d2.x/d1.x)-d2.x);
    a=(d1.y-b*d1.x)/d1.x/d1.x;
    if(a>0)
        return false;
    return true;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

void pre()//预处理
{
    scanf("%d %d",&n,&m);
    memset(f,0x3f,sizeof(f));//先赋极大值
    cnt=0;//cnt为抛物线的数量
    point pig[18];
    for(int i=0;i<n;i++)
        scanf("%lf %lf",&pig[i].x,&pig[i].y);
    for(int i=0;i<n;i++)
    {
        para[cnt++]=1<<i;//先加入一个新抛物线
        for(int j=i+1,vis=0;j<n;j++)//定义的vis是枚举过的小猪，避免重复
        {
            if((1<<j)&vis)//判重
                continue;
            double a,b;
            if(!calc(pig[i],pig[j],a,b))//如果不合法
                continue;
            para[cnt]=1<<i;//先暂时加进去只有第一只猪猪的抛物线
            for(int k=j;k<n;k++)//然后枚举加新点进去
            {
                if(ison(pig[k],a,b))//如果第k只猪猪在上面
                {
                    vis|=(1<<k);//更新vis数组
                    para[cnt]|=(1<<k);//更新抛物线
                }
            }
            cnt++;//然后抛物线的条数要加一
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        pre();
        f[0]=0;
        for(int i=0;i<(1<<n);i++)//枚举每个状态
            for(int j=0;j<cnt;j++)//枚举每一条抛物线
                f[i|para[j]]=min(f[i|para[j]],f[i]+1);//状态转移
        printf("%d\n",f[(1<<n)-1]);//输出答案
    }
    return 0;
}