#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a[maxn], n;

int main(){
    cin >> n;
    for (int i = 0; i < n; cin >> a[i++]);
    sort(a, a + n);
    int res = 0;
    for (int i = 0; i < n; i++){
        int k = i;
        while (a[k] == a[i] && i < n) k++;
        // cout << i << ' ' << k << endl;
        res = max(res, k - i);
        i = k - 1;
    }
    cout << res;
    return 0;
}