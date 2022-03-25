#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 30 + 5;

int res[maxn], n;

int main(){
    res[0] = res[1] = 1;
    for (int i = 2; i < maxn; i++) res[i] = 2 * (res[i - 1] + 1);
    while (cin >> n){
        cout << res[n] << endl;
    }
    return 0;
}