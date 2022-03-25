#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, k;
vector<int> v;

int main(){
    cin >> n >> k; int m = n;
    for (int i = 2, flag = 1; i <= n && flag; i++){
        if (n % i == 0){
            while (n % i == 0){
                v.push_back(i);
                n /= i;
            }
            if (v.size() > k) break;
        }
    }
    if (v.size() < k) {
        puts("-1");
    }
    else {
        int tot = 1;
        for (int i = 0; i < k - 1; i++){
            printf("%d ", v[i]); tot *= v[i];
        }
        printf("%d", m / tot);
    }
    return 0;
}