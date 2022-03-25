#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, r;
char f[] = "0123456789ABCDEF";

int main(){
    while (cin >> n >> r){
        int flag = 0;
        vector<char> res;
        if (n < 0) flag = 1, n = -n;
        while (n){
            res.push_back(f[n % r]);
            n /= r;
        }
        if (flag) cout << '-';
        for (int i = res.size() - 1; i >= 0; i--){
            cout << res[i];
        }
        cout << endl;
    }
    return 0;
}