#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn], b[maxn];

int main(){
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n); 
    int res = 0, p = 0;
    for (int i = 0; i < n; i++){
        while (p < n && a[p] <= a[i]) p++;
        if (a[i] < a[p]) p++, res++;
    }
    cout << res;
    return 0;
}