#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int a[maxn], n;

int main(){
    int n, s = 0;
    cin >> n;
    for (int i = 0; i < n; cin >> a[i], s += a[i], i++);
    sort(a, a + n);
    double avg = double(s) / double(n);
    int res = int(avg + 0.5);
    if (res == 5){
        cout << 0;
        return 0;
    }
    for (int i = 0; i < n; i++){
        s = s - a[i] + 5;
        res = int(double(s) / double(n) + 0.5);
        if (res == 5){
            cout << i + 1;
            return 0;
        }
    }
    return 0;
}