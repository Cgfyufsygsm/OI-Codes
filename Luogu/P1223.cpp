#include <cstdio>
#include <algorithm>
using namespace std;
class ren
{
public:
    int n;
    int time;
};
bool cmp(ren a,ren b)
{
    return a.time<b.time;
}
int main()
{
    int n;scanf("%d",&n);
    ren people[n];
    for(int i=0;i<n;i++)
    {
        people[i].n=i+1;
        scanf("%d",&people[i].time);
    }
    sort(people,people+n,cmp);
    long long sum=0;
    for(int i=0;i<n;i++)
    {
        printf("%d ",people[i].n);
        long long temp=people[i].time*(n-1-i);
        sum+=temp;
    }
    double avg=(double)sum/n;
    printf("\n%.2f",avg);
    return 0;
}