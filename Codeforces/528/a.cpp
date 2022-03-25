#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn]; int n;

int main(){
    cin >> s; n = strlen(s);
    if (n == 1) return cout << s, 0;
    string ans;
    if (n % 2) ans.push_back(s[n / 2]);
    for (int i = 0; i < n / 2; i++) {
        if (n % 2) {
            ans.push_back(s[n / 2 + 1 + i]);
            ans.push_back(s[n / 2 - 1 - i]);
        } else {
            ans.push_back(s[n / 2 - i - 1]);
            ans.push_back(s[n / 2 + i]);
        }
    }
    cout << ans;
    return 0;
}