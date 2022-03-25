#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

ll n;

int main(){
    cin >> n;
    if (n % 2) puts("1");
    else puts("2");
    return 0;
}