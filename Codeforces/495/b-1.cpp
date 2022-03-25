#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m;

int main(){
    cin >> n >> m;
    while (m--){
        int x, y; cin >> x >> y;
    }
    for (int i = 0; i < n; i++){
        cout << char(i % 2 + '0');
    }
    return 0;
}