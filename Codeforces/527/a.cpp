#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, k;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        cin >> n >> k;
        for (int i = 0; i < n; i++) printf("%c", 'a' + (i % k));
        puts("");
    }
    return 0;
}