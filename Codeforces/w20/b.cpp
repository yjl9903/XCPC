#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
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
const int maxn = 1000000 + 5;

int n, k; char s[maxn];

int main() {
    scanf("%d%d%s", &n, &k, s);
    if (k == 0) return puts(s), 0;
    for (int i = 0; i < n && k > 0; i++) {
        if ('z' - s[i] > s[i] - 'a') {
            if ('z' - s[i] < k) {
                k -= 'z' - s[i];
                s[i] = 'z'; 
            } else {
                if (s[i] + k <= 'z') {
                    s[i] += k; k = 0;
                } else {
                    assert(0);
                }
            }
        } else {
            if (s[i] - 'a' < k) {
                k -= s[i] - 'a';
                s[i] = 'a'; 
            } else {
                if (s[i] - k >= 'a') {
                    s[i] -= k; k = 0;
                } else {
                    assert(0);
                }
            }
        }
        dbg(k);
    }
    if (k > 0) puts("-1");
    else puts(s);
    return 0;
}