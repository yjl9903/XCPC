#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 100000 + 5;

int mark[maxn], prime[maxn], cnt = 0;
void sieve(){
    for (int i = 2; i <= maxn; i++){
        if (!mark[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && i * prime[j] <= maxn; j++){
            mark[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main(){
    sieve(); int n;
    while (cin >> n && n){
        cout << mark[n] << endl;
    }
    return 0;
}