#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 1e6 + 5;
char str[maxn];
int n, a[maxn], mark[maxn];

struct node {
    char ch;
    int sum, num;
    node *ls, *rs;
};

il node* newnode(char c, node *l = NULL, node *r = NULL, int num = -1) {
    node *cur = new node;
    cur->ch = c, cur->ls = l, cur->rs = r, cur->num = num;
    return cur;
}

node* stk[maxn];
int top;

int dfs1(node *u) {
    if (u->ch == 0 || u->ch == 1) return u->sum = u->ch;
    if (u->ch == '&')
        return u->sum = dfs1(u->ls) & dfs1(u->rs);
    else if (u->ch == '|')
        return u->sum = dfs1(u->ls) | dfs1(u->rs);
    else return u->sum = !dfs1(u->ls);
}

void dfs2(node *u) {
    if (u->ch == 0 || u->ch == 1) {
        mark[u->num] = 1;
        return;
    }
    int lv = u->ls->sum, rv;
    if (u->rs != NULL) rv = u->rs->sum;
    if (u->ch == '&') {
        if (lv == 1) dfs2(u->rs);
        if (rv == 1) dfs2(u->ls);
    } else if (u->ch == '|') {
        if (lv == 0) dfs2(u->rs);
        if (rv == 0) dfs2(u->ls);
    } else dfs2(u->ls);
}

int main() {
    fgets(str + 1, 1e6 + 2, stdin);
    scanf("%d", &n);
    FOR(i, 1, n) scanf("%d", a + i);
    for (int i = 1; str[i]; ++i) {
        if (str[i] != ' ') {
            if (str[i] == 'x') {
                int k = 0;
                ++i;
                while (isdigit(str[i])) k = 10 * k + (str[i++] - '0');
                stk[++top] = newnode(a[k], NULL, NULL, k);
            } else if (str[i] == '&') {
                node *x1 = stk[top--], *x2 = stk[top--];
                stk[++top] = newnode('&', x1, x2);
            } else if (str[i] == '|') {
                node *x1 = stk[top--], *x2 = stk[top--];
                stk[++top] = newnode('|', x1, x2);
            } else if (str[i] == '!') {
                node *x = stk[top--];
                stk[++top] = newnode('!', x);
            }
        }
    }

    dfs1(stk[top]);
    dfs2(stk[top]);

    int q;
    scanf("%d", &q);
    while (q--) {
        int x; scanf("%d", &x);
        printf("%d\n", mark[x] ? !stk[top]->sum : stk[top]->sum);
    }
    return 0;
}