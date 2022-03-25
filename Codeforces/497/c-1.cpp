#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn];

int main(){
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    int i = 0, m = 0;
    while (i < n){
        int x = a[i], t = 0;
        while (a[i] == x) i++, t++;
        m = max(m, t);
    }
    cout << n - m;
    return 0;
}