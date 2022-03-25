#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 55 + 5;

int n, res[maxn];

int main(){
    res[0] = res[1] = 1; res[2] = 2; res[3] = 3; res[4] = 4;
    for (int i = 5; i < maxn; i++){
        res[i] = res[i - 3] + res[i - 1];
    }
    while (cin >> n && n){
        cout << res[n] << endl;
    }
    return 0;
}