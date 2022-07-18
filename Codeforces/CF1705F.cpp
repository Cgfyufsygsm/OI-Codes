#include <bits/stdc++.h>
using namespace std;

int n;

int query(string s) {
    cout << s << endl;
    cout.flush();
    int x; cin >> x;
    if (x == n) puts(n > 100 ? "sb" : ""), exit(0);
    return x;
}

int main() {
    cin >> n;
    string allT(n, 'T'), ans(n, '?');
    int cntT = query(allT);

    string allTF(n, 'T');
    for (int i = 1; i < n; i += 2) allTF[i] = 'F';
    int cntTF = query(allTF);

    int l = 0, r = n - 1;
    while (r >= l) {
        if (r == l) {
            string s(allT);
            s[l] = 'F';
            int k = query(s);
            if (k > cntT) ans[l] = 'F';
            else ans[l] = 'T';
            ++l, --r;
        } else {
            string s(allT);
            s[l] = 'F', s[l + 1] = 'F';
            int k = query(s) - cntT;
            if (k == 2) {
                ans[l] = ans[l + 1] = 'F';
                l += 2;
            } else if (k == -2) {
                ans[l] = ans[l + 1] = 'T';
                l += 2;
            } else {
                if (r == l + 1) {
                    s = allT, s[l] = 'F';
                    int k = query(s);
                    if (k > cntT) ans[l] = 'F', ans[l + 1] = 'T';
                    else ans[l] = 'T', ans[l + 1] = 'F';
                    l += 2;
                } else {
                    s = allTF;
                    s[l] = 'F', s[l + 1] = 'T';
                    if (s[r] == 'F') s[r] = 'T';
                    else s[r] = 'F';

                    int k = query(s) - cntTF;
                    if (k == 3) ans[l] = 'F', ans[l + 1] = 'T', ans[r] = s[r];
                    else if (k == 1) ans[l] = 'F', ans[l + 1] = 'T', ans[r] = allTF[r];
                    else if (k == -1) ans[l] = 'T', ans[l + 1] = 'F', ans[r] = s[r];
                    else ans[l] = 'T', ans[l + 1] = 'F', ans[r] = allTF[r];

                    l += 2, --r;
                }
            }
        }
    }
    query(ans);
    return 0;
}