#include <cstdio>
#include <cctype>
#include <cmath>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 3e6 + 5;
const double pi = acos(-1.0);

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

template<typename T> inline void myswap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
    return;
}

struct cmplx
{
    double x, y;
    cmplx(double xx = 0, double yy = 0)
    {
        x = xx, y = yy;
    }
} a[maxn], b[maxn];

int rev[maxn];

cmplx operator+(const cmplx &a, const cmplx &b) {return cmplx(a.x + b.x, a.y + b.y);}
cmplx operator-(const cmplx &a, const cmplx &b) {return cmplx(a.x - b.x, a.y - b.y);}
cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

void DFT(int lim, cmplx *a, int type)
{
    FOR(i, 0, lim - 1)
        if (i < rev[i])
            myswap(a[i], a[rev[i]]);//先预处理翻转完了的结果
    for (int p = 2; p <= lim; p <<= 1)//模拟合并答案的过程，即为所谓的 n
    {
        int len = p >> 1;//即上面的 n / 2
        cmplx Wp = cmplx(cos(2 * pi / p), type * sin(2 * pi / p));//处理出 p 次单位根
        for (int k = 0; k < lim; k += p)//对每一个进行合并
        {
            cmplx w = cmplx(1, 0);//处理 \omega_p^0
            for (int l = k; l < k + len; ++l, w = w * Wp)//开始合并
            {
                //此时的 a[l] 就是之前的 a1[i]，a[len + l] 就是之前的 a2[i]
                cmplx tmp = w * a[len + l];
                a[len + l] = a[l] - tmp;//相当于上面的 a[i + (lim >> 1)] = a1[i] - w * a2[i]
                a[l] = a[l] + tmp;//相当于上面的 a[i] = a1[i] + w * a2[i]
            }
        }
    }
}

int main()
{
    int n = read(), m = read();
    FOR(i, 0, n) a[i].x = read();
    FOR(i, 0, m) b[i].x = read();
    int lim = 1;
    while (lim <= n + m) lim <<= 1;
    FOR(i, 0, lim - 1)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0));
    DFT(lim, a, 1);
    DFT(lim, b, 1);
    FOR(i, 0, lim)
        a[i] = a[i] * b[i];
    DFT(lim, a, -1);
    FOR(i, 0, n + m)
        printf("%d ", (int)(a[i].x / lim + 0.5));
    return 0;
}