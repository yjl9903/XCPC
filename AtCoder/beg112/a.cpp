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
    cin >> n;
    if (n == 1) return puts("Hello World"), 0;
    cin >> a >> b;
    cout << a + b;
    return 0;
}