#include <cstdio>
#include <cctype>
#include <set>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5, maxm = 7e6 + 5;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

std::set<int> st;

typedef std::set<int>::iterator IT;

struct node
{
    int ls, rs, sum;
} t[maxm];

#define L(k) t[k].ls
#define R(k) t[k].rs
#define M ((i + j) >> 1)

int root[maxm], pool[maxm], top, cnt;
int n, q, flag[maxn];

il int newnode() {return top ? pool[top--] : ++cnt;}

il void delnode(int k)
{
    if (!k) return;
    t[k].ls = t[k].rs = t[k].sum = 0, pool[++top] = k;
    return;
}

il void pushup(int k) {t[k].sum = t[L(k)].sum + t[R(k)].sum; return;}

void insert(int &k, int i, int j, int pos)
{
    if (!k) k = newnode();
    if (i == j)
    {
        ++t[k].sum;
        return;
    }
    if (pos <= M) insert(L(k), i, M, pos);
    else insert(R(k), M + 1, j, pos);
    pushup(k);
    return;
}

void split(int k1, int &k2, int k, int flag)//分裂 k1，留下 k 个元素，剩下给 k2
{
    if (t[k1].sum == k) return;
    k2 = newnode();
    t[k2].sum = t[k1].sum - k;
    t[k1].sum = k;
    if (t[L(k1)].sum + t[R(k1)].sum == 0) return;
    if (flag) std::swap(L(k1), R(k1)), std::swap(L(k2), R(k2));
    if (k <= t[L(k1)].sum) split(L(k1), L(k2), k, flag), R(k2) = R(k1), R(k1) = 0;
    else split(R(k1), R(k2), k - t[L(k1)].sum, flag);
    if (flag) std::swap(L(k1), R(k1)), std::swap(L(k2), R(k2));
    return;
}

IT split(int p)//将 p 所在的区间分裂出来
{
    IT it = st.lower_bound(p);//返回第一个左端点大于等于 p 的区间的左端点
    if (it != st.end() && *it == p) return it;
    --it;//找到真正需要分裂开的区间
    split(root[*it], root[p], p - *it, flag[p] = flag[*it]);//让 it 中保留 p - *it 个元素，剩下的给 p
    return st.insert(p).first;//返回这个区间对应的迭代器
}

void merge(int &k1, int k2)
{
    if (!k1 || !k2)
    {
        k1 |= k2;
        return;
    }
    t[k1].sum += t[k2].sum;
    merge(L(k1), L(k2));
    merge(R(k1), R(k2));
    delnode(k2);
    return;
}

void query(int k, int i, int j, int *cnt)
{
    if (i == j || !t[k].sum)
    {
        cnt[i] += t[k].sum;
        return;
    }
    if (L(k)) query(L(k), i, M, cnt);
    if (R(k)) query(R(k), M + 1, j, cnt);
    return;
}

char s[maxn];

int main()
{
    n = read(), q = read();
    scanf("%s", s + 1);
    FOR(i, 1, n) insert(root[i], 1, 26, s[i] - 'a' + 1), st.insert(i);
    FOR(i, 1, q)
    {
        int l = read(), r = read(), op = read();
        IT it2 = split(r + 1), it1 = split(l);
        for (IT i = ++it1; i != it2; ++i) merge(root[l], root[*i]);
        flag[l] = (op ^ 1);
        st.erase(it1, it2);
    }
    int cnt[27];
    for (IT it = st.begin(); it != st.end(); ++it)
    {
        int l = *it;
        memset(cnt, 0, sizeof cnt);
        query(root[l], 1, 26, cnt);
        if (!flag[l])
            FOR(i, 1, 26)
                FOR(j, 1, cnt[i])
                    putchar(i + 'a' - 1);
        else
            DEC(i, 26, 1)
                FOR(j, 1, cnt[i])
                    putchar(i + 'a' - 1);
    }
    return 0;
}