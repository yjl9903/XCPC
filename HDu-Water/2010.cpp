#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int x[maxn], cnt = 0;

int main(){
    for (int i = 100; i <= 999; i++){
        int a = i % 10, b = (i % 100 - a) / 10, c = (i - 10 * b - a) / 100;
        int s = a * a * a + b * b * b + c * c * c;
        if (s == i) x[cnt++] = i;
    }
    int m, n;
    while (cin >> m >> n){
        int k = 0;
        for (int i = 0; i < cnt; i++){
            if (x[i] > n) break;
            if (x[i] >= m){
                if (k++) cout << ' ';
                cout << x[i];
            }
        }
        if (!k) cout << "no";
        cout << endl;
    }
    return 0;
}