#include <bits/stdc++.h>
#define ll long long
#define ui unsigned
#define db double
#define mp make_pair
#define FOR(i, j, k) for(int i = (j); i <= (k); i++)
#define DEC(i, j, k) for(int i = (j); i >= (k); i--)
#define VIS(i, j) for(int i = head[j]; i; i = edge[i].nxt)
#define VEC(i, j) for(int i = 0; i < j.size(); i++)
using namespace std;

inline int read() {
  int res = 0; bool flag = 0; char ch = getchar();
  while(ch < '0' || ch > '9') {if(ch == '-') flag = 1; ch = getchar();}
  while('0' <= ch && ch <= '9') {res = (res << 1) + (res << 3) + (ch ^ 48); ch = getchar();}
  return flag ? -res : res;
}

char str[] = "aue1j0ghtrpmk256";

signed main() {
  srand(time(0));
  int t = 10;
  while(t--) {
    int n = rand() % 3 + 3;
    FOR(i, 1, n) putchar(str[rand() % 16]);
    putchar('\n');
  }
  return 0;
}