#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++){
        if (i) cout << ' ';
        if (a[i] % 2 == 0){
            a[i]--;
        }
        cout << a[i];
    }
    return 0;
}