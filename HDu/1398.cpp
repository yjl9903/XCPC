#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300 + 5;

int c1[maxn], c2[maxn], coin[18];

int main(){
    for (int i = 1; i <= 17; i++) coin[i] = i * i;
    c1[0] = 1;
    for (int i = 1; i <= 17; i++){
        for (int j = 0; j < maxn; j += i * i){
            for (int k = 0; j + k < maxn; k++){
                c2[j + k] += c1[k];
            }
        }
        for (int j = 0; j < maxn; j++) c1[j] = c2[j], c2[j] = 0;
    }
    int n;
    while (cin >> n && n) cout << c1[n] << endl;
    return 0;
}