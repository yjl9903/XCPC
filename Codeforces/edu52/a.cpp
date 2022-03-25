#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll a, b, c, s;

int main(){
    int T; cin >> T;
    while (T--){
        cin >> s >> a >> b >> c;
        ll n = s / c;
        cout << n + n / a * b << endl;
    }
    return 0;
}