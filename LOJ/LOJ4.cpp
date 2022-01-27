#include <cstdio>
char str[] = "#include <cstdio>%cchar str[] = %c%s%c;%cint main() {return printf(str, 10, 34, str, 34, 10), 0;}";
int main() {return printf(str, 10, 34, str, 34, 10), 0;}