#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

char s[30];

int main() {
    cin >> s;
    s[5] = 0;
    cout << (s + 6) << '-' << s; 
    return 0;
}