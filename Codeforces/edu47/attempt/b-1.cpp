#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];

bool cmp(char a, char b){
    if (a == '1' && b == '0') return 0;
    if (a == '2' && b == '1') return 0;
    return 1;
}

int main(){
    ms(s, 0);
    cin >> s;
    int res = 0, i = 0, j = 0, len = strlen(s);
    sort(s, s + len, cmp);
    cout << s;
    return 0;
}