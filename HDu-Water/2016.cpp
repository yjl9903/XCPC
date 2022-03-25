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
        for (int i = 0; i < n; cin >> a[i++]);
        int m = a[0], k = 0;
        for (int i = 1; i < n; i++){
            if (a[i] < m){
                m = a[i]; k = i;
            }
        }
        swap(a[0], a[k]);
        for (int i = 0; i < n; i++){
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}