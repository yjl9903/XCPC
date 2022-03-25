#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
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
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

vector<int> dep[maxn];
int n, a[maxn], b[maxn], vis[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", b + i);
        dep[(i - b[i] % n + n) % n].push_back(b[i]);
    }
    int last = 0;
    for (int i = 0; i < n; i++) {
        sort(dep[i].begin(), dep[i].end());
        for (int& x: dep[i]) a[last++] = x;
    }
    for (int i = 0; i < n; i++) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    return 0;
}