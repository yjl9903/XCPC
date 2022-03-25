#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int a[maxn], n, sum = 0, cnt = 0, sum2 = 0;

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n;
        sum = cnt = sum2 = 0;
        for (int i = 0; i < n; i++){
            int x; cin >> x;
            if (x % 2) a[cnt++] = x, sum2 += x - 1;
            else sum += x;
        }
        if (cnt == 0) cout << sum << endl;
        else{
            int avg = (sum + sum2) / cnt;
            if (avg % 2)
                cout << avg << endl;
            else 
                cout << avg + 1 << endl;
        }
    }
    return 0;
}
