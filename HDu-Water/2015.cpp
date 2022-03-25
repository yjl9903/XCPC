#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m;

int main(){
    while (cin >> n >> m){
        n *= 2; int t = 0, s = 0, k = 0;
        for (int i = 2; i <= n; i += 2){
            s += i; t++;
            if (t == m){
                if (k++) cout << ' ';
                cout << s / t;
                s = t = 0;
            }
        }
        if (t){
            if (k++) cout << ' ';
            cout << s / t;
        }
        cout << endl;
    }
    return 0;
}