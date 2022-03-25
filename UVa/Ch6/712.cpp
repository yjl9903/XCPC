#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int a[maxn], b[maxn], f[10], n, m;

int main(){
    int kase = 0;
    while (cin >> n && n){
        char x[5];
        for (int i = 1; i <= n; i++){
            cin >> x;
            f[x[1] - '0'] = i;
        }
        char t;
        for (int i = 0; i < (1 << n); i++){
            cin >> t;
            a[i] = t - '0';
        }
        //for (int i = 1; i <= n; cout << f[i++]);cout << endl;
        //for (int i = 0; i < (1 << n); cout << a[i++]);cout << endl;

        cin >> m;
        cout << "S-Tree #" << ++kase << ":\n";
        while (m--){
            int x = 0;
            for (int i = 1; i <= n; i++){
                cin >> t;
                b[f[i]] = t - '0';
            }
            //for (int i = 1; i <= n; cout << b[i++]);cout << endl;
            for (int i = 1; i <= n; i++){
                x = x * 2 + b[i];
            }
            cout << a[x];
        }
        cout << endl << endl;
    }
    return 0;
}