#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a, b, c, n;

int main(){
    cin >> a >> b >> c >> n;
    if (a + b - c >= n || a < c || b < c){
        cout << -1;
    }
    else{
        cout << n - (a + b - c);
    }
    return 0;
}