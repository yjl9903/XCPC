#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    cin >> n;
    if (n % 3 == 0 || n % 3 == 1){
        printf("1 1 %d", n - 2);
    }
    else printf("1 2 %d", n - 3);
    return 0;
}