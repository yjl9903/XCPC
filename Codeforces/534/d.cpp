#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

string s;
int query(int a, int b) {
    cout << "? " << a << " " << b << endl;
    char s[5]; cin >> s;
    return s[0] - 'x';
}

// 1 % a, 2 % a, 4 % a, ... , 2^n % a

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> s) {
        if (s == "end" || s == "mistake") break;
        int mx = 30;
        for (int i = 1; i <= 29; i++) {
            int x = query(1 << (i - 1), 1 << i);
            if (x == 0) {
                mx = i; break;
            }
        }
        // cout << "ha " << mx << endl;
        int l = 1 << (mx - 1), r = (1 << mx) + 1;
        while (l < r) {
            int m = (l + r) >> 1;
            // cout << m << ' ' << l << ' ' << r << endl;
            if (query(r, m) == 1) l = m + 1;
            else r = m;
        }
        cout << "! " << r << endl;
    }
    return 0;
}