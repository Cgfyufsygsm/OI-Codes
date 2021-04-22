extern "C" int Seniorious(int);

extern "C" int Chtholly(int n,int c)
{
    int l=1,r=n,ans;
    while(l<=r)
    {
        int mid=l+r>>1,t=Seniorious(mid);
        if(t==0)
            return mid;
        if(t<0)
            l=mid+1;
        else
            ans=r=mid-1;
    }
    return ans;
}