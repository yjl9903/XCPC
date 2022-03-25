#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a, b;

int main(){
    int T; cin >> T;
    while (T--){
        cin >> a >> b;
        if (a % b == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}