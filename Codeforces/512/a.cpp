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
    cin >> n; int flag = 1;
    for (int i = 0, x; i < n; i++){
        cin >> x;
        if (x == 1) flag = 0;
    }
    if (flag) puts("EASY");
    else puts("HARD");
    return 0;
}