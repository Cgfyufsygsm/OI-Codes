#include <cstdio>
#include <cctype>
#include <string>
using namespace std;
int main()
{
    char mode;
    int b=0,k=0,tmp=0;
    bool equal=1,flag=1;
    string s;
    for(int i=0;;i++)
    {
        char c=getchar();
        if(c==EOF) break;
        s[i]=c;
        if(isalpha(c))
        {
            mode=c;
            if(s[i-1]=='-')
            {
                k+=equal?-1:1;
            }
            else if(s[i-1]=='+'||i==0||s[i-1]=='=')
            {
                k+=equal?1:-1;
            }
            else
            {
                k+=equal?tmp:-tmp;
                tmp=0;
            }
        }
        if(isdigit(c))
        {
            tmp*=10;
            tmp+=flag?(c-'0'):-(c-'0');
        }
        if(c=='+')
        {
            flag=1;
            b+=equal?-tmp:tmp;
            tmp=0;
        }
        if(c=='-')
        {
            flag=0;
            b+=equal?-tmp:tmp;
            tmp=0;
        }
        if(c=='=')
        {
            flag=1;
            b+=equal?-tmp:tmp;
            tmp=0;
            equal=0;
        }
        //rintf("c:%c,tmp:%d,k:%d,b:%d,equal:%d,flag:%d\n",c,tmp,k,b,equal,flag);
    }
    if(tmp!=0) b+=tmp;
    //printf(",tmp:%d,k:%d,b:%d,equal:%d,flag:%d\n",tmp,k,b,equal,flag);
    double ans=(double)b/k;
    if(ans==-0.0000) ans=0;
    printf("%c=%.3f",mode,ans);
    return 0;
}