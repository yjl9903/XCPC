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

char s[10], t[10];

int main(){
    cin >> s;
    for (int i = 0; i < 5; i++) {
        cin >> t;
        if (s[0] == t[0] || s[1] == t[1]) return puts("YES"), 0;
    }
    puts("NO");
    return 0;
}