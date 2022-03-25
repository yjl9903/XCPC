#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
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
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int a[maxn], b[maxn];

int main(){
    srand(time(NULL)); srand(rand()); srand(rand());
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        for (int i = 0; i < 12; i++) scanf("%d", a + i);
        int t = 5000, mx = 0;
        for (int i = 0; i < 12; i++) b[i] = a[i]; 
        sort(b, b + 12);
        for(int i=11;i>=2;)
        {
            // dbg(b[i], b[i - 1], b[i - 2]);
            if(b[i]<b[i-1]+b[i-2])mx++,i-=3;
            else i--;
        }
        // cout << mx << endl;
        while (t--) {
            random_shuffle(a, a + 12);
            int tot = 0;
            for (int i = 0; i < 12; i += 3) {
                sort(a + i, a + i + 3);
                if (a[i] + a[i + 1] > a[i + 2]) tot++;
            }
            if (tot > mx) {
                mx = tot;
                for (int i = 0; i < 12; i++) b[i] = a[i];
            }
            if (tot == 4) break;
        }
        printf("Case #%d: %d\n", ++kase, mx);
        for (int i = 0; i < 12; i += 3) {
            if (b[i] + b[i + 1] > b[i + 2]) {
                printf("%d %d %d\n", b[i], b[i + 1], b[i + 2]);
            }
        }
    }
    return 0;
} 