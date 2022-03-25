#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}
int lcm(int a, int b){return a / gcd(a, b) * b;}
int ex, ey, res = 0;

int main(){
    int T, kase = 0; cin >> T;
    while (T--){
        cin >> ex >> ey;
        res = 1;
        int k = gcd(ex, ey);

        if (ex < ey) swap(ex, ey);
        while(ex % (ey + k) == 0){
            res++;
            ex = ex / (ey / k + 1);
            if(ex < ey) swap(ex, ey);
        }
        cout << "Case #" << ++kase << ": ";
        cout << res << endl;
    }
    return 0;
}