#include<iostream>
int main()
{
    double s=0,k,n;
    std::cin>>k;
    for(n=1;;n++)
    {
        s+=(1/n);
        if(s>k)
        {
            std::cout<<n<<std::endl;
            break;
        }
    }
    return 0;
}