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

int n;

int main(){
    cin >> n;
    if (n % 4 == 0) puts("0");
    else if (n % 4 == 1) puts("1");
    else if (n % 4 == 2) puts("1");
    else puts("0");
    return 0;
}