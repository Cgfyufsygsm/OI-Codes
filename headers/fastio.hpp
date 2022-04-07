#ifndef YANGTY_FASTIO_HPP
#define YANGTY_FASTIO_HPP 1

#include <cstdio>
#include <cctype>

namespace YangTY {

namespace fastIO {

namespace internal {

class IObase {
  private:
    static const int maxc = 1 << 25;
    char ibuf[maxc];
    char obuf[maxc], *__oPos;

  public:
    inline char getchar() {
        static char *__iPos1 = ibuf, *__iPos2 = ibuf + fread(ibuf, 1, maxc, stdin);
        return __iPos1 == __iPos2 ? EOF : *__iPos1++;
    }

    inline void putchar(char c) {
        *__oPos++ = c;
    }

    IObase() {
        __oPos = obuf;
    }

    ~IObase() {
        fwrite(obuf, __oPos - obuf, 1, stdout);
    }
} base;

} // namespace internal

using internal::base;

class istream {
  public:
    int getInt();
    long long getLL();
    char getchar();
    friend istream& operator>>(istream&, char&);
    friend istream& operator>>(istream&, char*);
    template<class T> friend istream& operator>>(istream&, T&);
};

class ostream {
  public:
    friend inline ostream& operator<<(ostream&, const char&);
    friend ostream& operator<<(ostream&, const char*);
    friend ostream& operator<<(ostream&, char*);
    template<class T> friend ostream& operator<<(ostream&, T);
};

inline ostream& operator<<(ostream &out, const char &c) {
    base.putchar(c);
    return out;
}

ostream& operator<<(ostream &out, const char *s) {
    for (int i = 0; s[i]; ++i) out << s[i];
    return out;
}

ostream& operator<<(ostream &out, char *s) {
    for (int i = 0; s[i]; ++i) out << s[i];
    return out;
}

template<class T> ostream& operator<<(ostream &out, T x) {
    static char stk[50];
    int top = 0;
    if (x < 0) out << '-', x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) out << stk[top--];
    } else out << '0';
    return out;
}

istream& operator>>(istream &in, char &c) {
    c = base.getchar();
    while (~c && isspace(c)) c = base.getchar();
    return in;
}

istream& operator>>(istream &in, char *s) {
    static int pos;
    static char c;
    c = base.getchar(), pos = 0;
    while (~c && isspace(c)) c = base.getchar();
    while (~c && !isspace(c)) s[pos++] = c, c = base.getchar();
    return in;
}

template<class T> istream& operator>>(istream &in, T &x) {
    static int rev;
    static char c;
    rev = x = 0;
    c = base.getchar();
    while (~c && !isdigit(c)) rev |= (c == '-'), c = base.getchar();
    while (~c && isdigit(c)) x = 10 * x + c - '0', c = base.getchar();
    x = rev ? -x : x;
    return in;
}

int istream::getInt() {
    static int ret;
    *this >> ret;
    return ret;
}

long long istream::getLL() {
    static long long ret;
    *this >> ret;
    return ret;
}

char istream::getchar() {
    static char c;
    *this >> c;
    return c;
}

istream is;
ostream os;

} // namespace fastIO

} // namespace YangTY

#endif