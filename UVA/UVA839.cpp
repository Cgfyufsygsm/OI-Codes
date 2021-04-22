#include <cstdio>
#include <cctype>

inline int read_int()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

bool read(int &W)
{
    int WL=read_int(),DL=read_int(),WR=read_int(),DR=read_int();
    bool b1=true,b2=true;
    if(!WL)
        b1=read(WL);
    if(!WR)
        b2=read(WR);
    W=WL+WR;
    return b1 && b2 && WL*DL==WR*DR;
}

int main()
{
    int t=read_int();
    int W;
    while(t--)
    {
        printf("%s\n",read(W=0)?"YES":"NO");
        if(t)
            printf("\n");
    }
    return 0;
}