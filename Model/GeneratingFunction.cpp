// HDu1028 Ignatius and the Princess III

#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 120 + 5;

int c1[maxn], c2[maxn], n;

int main(){
    c1[0] = 1;
    for (int i = 1; i < maxn; i++){ // 1 + x ^ i + x ^ 2i + ... + x ^ ni
        for (int j = 0; j < maxn; j += i){
            for (int k = 0; j + k < maxn; k++){
                c2[j + k] += c1[k];
            }
        }
        for (int j = 0; j < maxn; j++){
            c1[j] = c2[j];
            c2[j] = 0;
        }
    }
    while (cin >> n){
        cout << c1[n] << endl;
    }
    return 0;
}