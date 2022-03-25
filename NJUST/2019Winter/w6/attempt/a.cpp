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

int a, b, r;

int main(){
    cin >> a >> b >> r;
    if (2 * r <= min(a, b)) puts("First");
    else puts("Second");
    return 0;
}