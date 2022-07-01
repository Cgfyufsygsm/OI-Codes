#include <cstdio>

const int SIZE = 100000000;
char buf[SIZE];

int main(int, char *argv[]) {
    std::FILE *fin = std::fopen(argv[1], "r");
    std::size_t cnt = std::fread(buf, sizeof(char), SIZE, fin);
    std::fclose(fin);
    std::FILE *fout = std::fopen(argv[1], "wb");
    std::fwrite(buf, sizeof(char), cnt, fout);
    std::fclose(fout);
    return 0;
}