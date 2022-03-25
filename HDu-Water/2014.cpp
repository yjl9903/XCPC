#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int a[maxn], n;

int main(){
    while (cin >> n){
        for (int i = 0; i < n; cin >> a[i++]);
        sort(a, a + n);
        int sum = 0;
        for (int i = 1; i < n - 1; i++) sum += a[i];
        double avg = double(sum) / double(n - 2);
        printf("%.2f\n", avg);
    }
    return 0;
}