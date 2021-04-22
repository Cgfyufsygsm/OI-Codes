#include <cstdio>
#include <cstring>

const int maxn=1000000+5;
char s[maxn];
int n;
int f[maxn];
int st,ed,maxl;

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
    {
        if((s[i]==']' && s[i-f[i-1]-1]=='[') || (s[i]==')' && s[i-f[i-1]-1]=='('))
        {
            f[i]=f[i-1]+2+f[i-f[i-1]-2];
            if(f[i]>maxl)
            {
                maxl=f[i];
                st=i-f[i]+1;
                ed=i;
            }
        }
    }
    for(int i=st;i<=ed;i++)
        putchar(s[i]);
    return 0;
}