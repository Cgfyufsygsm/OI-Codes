#include<algorithm>
#include<cstdio>

const int maxn = 2e5 + 5;
using namespace std;
int n, m, sl, fh, rt_num, a[maxn];
int b[maxn], rt[maxn];// b是表示升序(0)/降序(1)
struct val_seg {
    int l, r, sz;
}tre[maxn * 400];
struct seg {
    int mn, id, lt;
}tr[maxn << 2];
int rd() {
    sl = 0; fh = 1;
    char ch = getchar();
    while (ch < '0' || '9' < ch) { if (ch == '-') fh = -1; ch = getchar(); }
    while ('0' <= ch && ch <= '9') sl = sl * 10 + ch - '0', ch = getchar();
    return sl * fh;
}

void split(int no, int& x, int& y, int k) //分裂
{
    if (!no) return;
    if (tre[no].sz <= k) { x = no, y = 0; return; }
    else if (k <= 0) { x = 0, y = no; return; }
    x = ++rt_num; y = ++rt_num;
    tre[x].sz = k, tre[y].sz = tre[no].sz - k;
    split(tre[no].l, tre[x].l, tre[y].l, k);
    split(tre[no].r, tre[x].r, tre[y].r, k - tre[tre[no].l].sz);
}

void merge(int& no, int l, int r, int x, int y) //合并
{
    if (!x || !y) { no = x + y; return; }
    no = ++rt_num; tre[no].sz = tre[x].sz + tre[y].sz;
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge(tre[no].l, l, mid, tre[x].l, tre[y].l);
    merge(tre[no].r, mid + 1, r, tre[x].r, tre[y].r);
}

void ins(int& no, int l, int r, int x) //一开始对每个位置建的线段树
{
    if (!no) no = ++rt_num;
    tre[no].sz++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) ins(tre[no].l, l, mid, x);
    else ins(tre[no].r, mid + 1, r, x);
}

int find(int no, int l, int r, int k) //查找第k个
{
    if (l == r) return l;
    int mid = (l + r) >> 1, t = tre[tre[no].l].sz;
    if (k <= t) return find(tre[no].l, l, mid, k);
    else return find(tre[no].r, mid + 1, r, k - t);
}
// 下面这个是用来充当链表的，dalao可以自行跳过
void build(int no, int l, int r) {
    if (l == r) { tr[no].id = tr[no].mn = l; return; }
    int mid = (l + r) >> 1;
    build(no << 1, l, mid);
    build(no << 1 | 1, mid + 1, r);
    tr[no].mn = min(tr[no << 1].mn, tr[no << 1 | 1].mn);
}

void pushdown(int no) {
    if (tr[no].lt) {
        tr[no << 1].mn = tr[no << 1].id = tr[no << 1].lt = tr[no].lt;
        tr[no << 1 | 1].mn = tr[no << 1 | 1].id = tr[no << 1 | 1].lt = tr[no].lt;
        tr[no].lt = 0;
    }
}

void update(int no, int l, int r, int L, int R, int x) {
    if (r < L || R < l) return;
    if (L <= l && r <= R) { tr[no].mn = tr[no].id = tr[no].lt = x; return; }
    int mid = (l + r) >> 1;
    pushdown(no);
    if (L <= mid) update(no << 1, l, mid, L, R, x);
    if (R > mid) update(no << 1 | 1, mid + 1, r, L, R, x);
    tr[no].mn = min(tr[no << 1].mn, tr[no << 1 | 1].mn);
}

int query(int no, int l, int r, int x) {
    if (l == r) return tr[no].id;
    int mid = (l + r) >> 1;
    pushdown(no);
    if (x <= mid) return query(no << 1, l, mid, x);
    else return query(no << 1 | 1, mid + 1, r, x);
}

int ask(int no, int l, int r, int x) {
    if (l == r) {
        if (tr[no].id <= x) return l;
        else return 0;
    }
    int mid = (l + r) >> 1;
    pushdown(no);
    if (tr[no << 1 | 1].mn > x) return ask(no << 1, l, mid, x);
    else return ask(no << 1 | 1, mid + 1, r, x);
}

int getrt(int no, int l, int r, int x) {
    if (!x) return 0;
    if (l == r) return tr[no].id;
    int mid = (l + r) >> 1;
    pushdown(no);
    if (tr[no << 1 | 1].mn > x) return getrt(no << 1, l, mid, x);
    else return getrt(no << 1 | 1, mid + 1, r, x);
}

void solve(int l, int r, int flg) {
    int L, R, z, k, x, y;
    x = query(1, 1, n, l); k = ask(1, 1, n, x - 1); z = l - 1; //k表示前面那棵线段树维护区间的末尾位置
    if (!b[x]) split(rt[x], L, R, l - k - 1); //升序的话，直接将前面的分裂出去
    else split(rt[x], R, L, tre[rt[x]].sz - l + k + 1); //降序的话，在前面我们要的区间是前面的那些数
    //L是不需要的那些数，R是我们需要的
    if (L && R) //若其中一个为空，说明它已经独自成一个区间了
    {
        rt[z] = L, rt[z + 1] = R, b[z] = b[z + 1] = b[x];
        update(1, 1, n, k + 1, z, z); k = ask(1, 1, n, x); update(1, 1, n, z + 1, k, z + 1);
    }
    //下面是对区间最后一段的操作，和上面同理，L、R的意义与上面相反
    y = query(1, 1, n, r); k = ask(1, 1, n, y - 1); z = r + 1;
    if (!b[y]) split(rt[y], L, R, r - k);
    else split(rt[y], R, L, tre[rt[y]].sz - r + k);
    if (L && R) {
        rt[z] = R, rt[z - 1] = L, b[z] = b[z - 1] = b[y];
        update(1, 1, n, k + 1, z - 1, z - 1); k = ask(1, 1, n, y); update(1, 1, n, z, k, z);
    }
    l = query(1, 1, n, l); r = query(1, 1, n, r); x = l;
    for (int i = r; i != l; i = getrt(1, 1, n, i - 1)) merge(rt[l], 1, n, rt[l], rt[i]); //合并线段树
    l = ask(1, 1, n, l - 1) + 1; r = ask(1, 1, n, r);
    update(1, 1, n, l, r, x); b[x] = flg;
}

int get(int x) {
    int l = query(1, 1, n, x);
    x -= ask(1, 1, n, l - 1);
    if (!b[l]) return find(rt[l], 1, n, x);
    else return find(rt[l], 1, n, tre[rt[l]].sz - x + 1);
}

int fin[maxn];

int main() {
    n = rd(); m = rd(); int l, r, typ;
    int x = rd();
    for (int i = 1; i <= n; ++i) ins(rt[i], 1, n, rd());
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) typ = rd(), l = rd(), r = rd(), solve(l, r, typ == 2);
    for (int i = 1; i <= n; ++i) fin[i] = get(i);//, printf("%d ", fin[i]);
    int ans = 0;
    for (int i = 1; i <= n; ++i) if (fin[i] == x) {ans = i; break;}
    printf("%d\n", ans);
    return 0;
}