#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a[maxn], n;

int main(){
    while (cin >> n && n){
        int x, res = 0;
        for (int i = 0; i < n; i++){
            cin >> x;
            res += x / 100; 
            x %= 100;
            res += x / 50;
            x %= 50;
            res += x / 10;
            x %= 10;
            res += x / 5;
            x %= 5;
            res += x / 2;
            x %= 2;
            res += x;
        }
        cout << res << endl;
    }
    return 0;
}