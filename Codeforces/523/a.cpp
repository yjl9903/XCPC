#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, s;

int main(){
    cin >> n >> s;
    if (s <= n) return puts("1"), 0;
    cout << s / n + (s % n ? 1 : 0) << endl;
    return 0;
}