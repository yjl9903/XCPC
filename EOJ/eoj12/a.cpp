#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a, b;

int main(){
    cin >> n >> a >> b;
    cout << 1ll * (n - 2) * (b - a) + 1 << endl;
    return 0;
}