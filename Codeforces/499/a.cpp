#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

char s[maxn];
int n, k;

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> k >> s;
    int len = strlen(s), cnt = 0, i = 0, res = 0;
    sort(s, s + len);
    while (i < len){
        res += s[i] - 'a' + 1; cnt++;
        if (cnt == k) break;
        char a = s[i];
        while (s[i] <= a + 1) i++;
    }
    if (cnt == k){
        cout << res;
    }
    else {
        cout << -1;
    }
    return 0;
}