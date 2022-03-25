#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n; char s[maxn];

int main(){
    cin >> n >> s;
    int sum = 0;
    for (int i = 0; i < n; i++) sum += s[i] - '0';
    for (int i = 2; i <= n; i++){
        if (sum % i) continue;
        int x = sum / i, flag = 1, tot = 0;
        for (int j = 0; j < n; j++){
            tot += s[j] - '0';
            if (tot == x){
                tot = 0;
            }
            else if (tot > x){
                flag = 0; break;
            }
        }
        if (flag){
            puts("YES"); return 0;
        }
    }
    puts("NO");
    return 0;
}