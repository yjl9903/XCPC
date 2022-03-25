#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;



int main(){
    int T; cin >> T;
    while (T--){
        int h, m, s; cin >> h >> m >> s;
        double m2 = 1.0 * m + double(s) / 60.0;
        double h2 = h + m2 / 60.0;
        if (h2 >= 12) h2 -= 12;
        double k = fabs(m2 - h2 * 5);
        if (k >= 30) k = 60 - k;
        int d = k * 6.0;
        cout << d << endl;
    }
    return 0;
}