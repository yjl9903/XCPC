#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn];

int main(){
    while (gets(s)){
        if (s[0] == '#') break;
        ll sum = 0;
        int len = strlen(s);
        for (int i = 0; i < len; i++){
            if (s[i] < 'A' || s[i] > 'Z') continue;
            sum += (i + 1) * (s[i] - 'A' + 1);
        }
        printf("%lld\n", sum);
    }
    return 0;
}