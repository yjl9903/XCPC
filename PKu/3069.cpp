#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int pos[maxn], r, n, res;

int main(){
    while (cin >> r >> n){
        if (r == -1 && n == -1) return 0;
        for (int i = 0; i < n; cin >> pos[i++]);
        sort(pos, pos + n);
        res = 0;
        for (int i = 0; i < n; i++){
            int j = i;
            while (pos[j] - pos[i] <= r) j++;
            res++; 
            if (i != j){
                int k = j - 1;
                while (pos[k] - pos[j - 1] <= r) k++;
                i = k - 1;
            }
        }
        cout << res << endl;
    }
    return 0;
}