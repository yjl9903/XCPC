#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int x[maxn], n, d;

int main(){
    cin >> n >> d;
    for (int i = 0; i < n; cin >> x[i++]);
    sort(x, x + n);
    int res = 2;
    for (int i = 1; i < n; i++){
        if (x[i] - x[i - 1] > 2 * d) res += 2;
        else if (x[i] - x[i - 1] == 2 * d) res++;
    }
    cout << res;
    return 0;
}