#include <iostream>
#include <string>

using namespace std;

const string s[4] = {"ABC", "AHC", "ARC", "AGC"};
bool vis[4];

int main() {
    string a;
    for (int i = 1; i <= 3; ++i) {
        cin >> a;
        for (int j = 0; j <= 3; ++j)
            if (s[j] == a) vis[j] = 1;
    }
    for (int j = 0; j <= 3; ++j) if (!vis[j]) cout << s[j] << endl;
    return 0;
}