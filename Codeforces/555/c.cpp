#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int l = 1, r = n, last = 0;
    string ans;
    for (int i = 1; i <= n && l <= r; i++) {
        if (a[l] > last && a[r] > last) {
            if (a[l] == a[r]) {
                
            } else if (a[l] < a[r]) {
                ans.push_back('L');
                last = a[l]; l++;
            } else {
                ans.push_back('R');
                last = a[r]; r--;
            }
        } else if (a[l] > last) {
            ans.push_back('L');
            last = a[l]; l++;
        } else if (a[r] > last) {
            ans.push_back('R');
            last = a[r]; r--;
        } else break;
    }
    cout << (int)ans.size() << '\n' << ans;
    return 0;
}