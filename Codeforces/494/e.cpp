#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 400000 + 5;

int n, d, k, cnt = 1;
int pre[maxn];

int dfs1(int p){
    
    pre[++cnt] = p;
    dfs1(p + 1);
}

int main(){
    cin >> n >> d >> k;
    ms(pre, 0);
    int flag = dfs1(1);
    return 0;
}