#include "game.h"

const int maxn = 1505;
int cnt[maxn];
int max(int a, int b) {return a > b ? a : b;}

void initialize(int n) {}

int hasEdge(int u, int v) {return ++cnt[max(u, v)] == max(u, v);}