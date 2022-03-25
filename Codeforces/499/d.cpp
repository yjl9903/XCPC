#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

inline int act(int x){
    cout << x << endl << flush;
    cin >> x;
    return x;
}
int m, n, a[40] = {0};

int main(){
    ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 0; i < n; i++){
        a[i] = act(1);
        if (a[i] == 0) return 0;
    }
    int l = 1, r = m, cnt = 0;
    while (l <= r){
        int m = (l + r) >> 1;
        int res = act(m) * a[(cnt++) % n];
        if (res == 0) return 0;
        if (res < 0) r = m - 1;
        else l = m + 1;
    }
    return 0;
}