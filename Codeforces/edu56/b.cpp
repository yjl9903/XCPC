#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

string s;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        cin >> s;
        int flag = 1;
        for (int i = 1; i < s.length(); i++) if (s[i] != s[0]) {
            flag = 0; break;
        }
        if (flag) puts("-1");
        else {
            sort(s.begin(), s.end());
            cout << s << endl;
        }
    }
    return 0;
}