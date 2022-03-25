#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m;
int a[maxn];

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a, a + n);
        int k = 100 - a[0];
        cout << k * k << endl;
    }
    return 0;
}