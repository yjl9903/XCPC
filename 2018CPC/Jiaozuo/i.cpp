#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a, b, c;

int main(){
    while (~scanf("%d%d%d", &a, &b, &c)){
        if (a == 1 && b == 1 && c == 1){
            puts("No"); continue;
        }
        if (a % 2 == 0 || c % 2 == 0 || b % 2 == 0){
            puts("Yes");
        }
        else puts("No");
    }
    return 0;
}