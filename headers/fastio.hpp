#ifndef YANGTY_FASTIO_HPP
#define YANGTY_FASTIO_HPP 1

#include <cstdio>
#include <cctype>

namespace YangTY {

namespace fastIO {

namespace internal {

class IObase {
  private:
    char *iPos, *iEnd, *oPos, *oEnd, *iBuf, *oBuf;
    int iBufSize, oBufSize, flag;

  public:
    inline char getchar() {
        if (iBuf == nullptr || iPos == iEnd) {
            if (iBuf) {
                delete[] iBuf;
                iBuf = nullptr;
            }
            if (!flag) return EOF;
            iBufSize <<= 1;
            iBuf = new char[iBufSize];
            int readSize = fread(iBuf, 1, iBufSize, stdin);
            flag &= (readSize == iBufSize);
            iPos = iBuf, iEnd = iPos + readSize;
        }
        return *iPos++;
    }

    inline void putchar(char c) {
        if (oBuf == nullptr || oPos == oEnd) {
            if (oBuf) {
                fwrite(oBuf, oEnd - oBuf, 1, stdout);
                delete[] oBuf;
                oBuf = nullptr;
            }
            oBufSize <<= 1;
            oBuf = new char[oBufSize];
            oPos = oBuf, oEnd = oBuf + oBufSize;
        }
        *oPos++ = c;
        return;
    }

    IObase() {
        iBuf = oBuf = nullptr;
        iPos = iEnd = oPos = oEnd = nullptr;
        flag = 1, iBufSize = oBufSize = 1 << 20;
    }

    ~IObase() {
        fwrite(oBuf, oPos - oBuf, 1, stdout);
        if (iBuf) delete[] iBuf;
        if (oBuf) delete[] oBuf;
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