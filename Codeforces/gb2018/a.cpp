#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int y, b, r;

int main(){
    cin >> y >> b >> r;
    int ans = min(y, min(b - 1, r - 2));
    cout << ans * 3 + 3;
    return 0;
}