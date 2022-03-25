#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 50 + 5;

int n, t; char s[maxn];

int main(){
    scanf("%d%d%s", &n, &t, s);
    for (int _ = 0; _ < t; _++) {
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == 'B' && s[i + 1] == 'G') {
                swap(s[i], s[i + 1]); i++;
            }
        }
    }
    cout << s << endl;
    return 0;
}