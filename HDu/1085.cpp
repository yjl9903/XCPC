#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;

int num[3], coin[3] = {1, 2, 5}, c1[maxn], c2[maxn];

int main(){
    while (cin >> num[0] >> num[1] >> num[2]){
        if (!num[0] && !num[1] && !num[2]) return 0;
        ms(c1, 0); ms(c2, 0); c1[0] = 1;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j <= num[i] * coin[i] && j < maxn; j += coin[i]){
                for (int k = 0; j + k < maxn; k++){
                    c2[j + k] += c1[k];
                }
            }
            for (int j = 0; j < maxn; j++) c1[j] = c2[j], c2[j] = 0;
        }
        int res = 0;
        for (int i = 0; i < maxn; i++) if (!c1[i]){
            res = i; break;
        }
        cout << res << endl;
    }
    return 0;
}