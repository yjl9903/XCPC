#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int check(int x){
    if (x == 1 || x == 2 || x == 3) return 0;
      
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        if (n == 1 || n == 2) puts("4");
        else if (n == 3 || n == 4) puts("6");
        else {
            
        }
    }
    return 0;
}