#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int a[maxn], n, m;

int main(){
    while (cin >> n >> m){
        if (!n && !m) break;
        for (int i = 0; i < n; cin >> a[i++]);
        a[n] = m;
        sort(a, a + n + 1);
        for (int i = 0; i < n + 1; i++){
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}