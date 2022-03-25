#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int h, m;
char s[30];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d %s", &h, &m, s);
        int f = 1, d, d2 = 0;
        if (s[3] == '+') f = 1; else if (s[3] == '-') f = -1;
        d = s[4] - '0';
        if (s[5] >= '0' && s[5] <= '9') {
            d = d * 10 + s[5] - '0';
            if (s[6] == '.')
                d2 = s[7] - '0';
        }
        else if (s[5] == '.'){
            d2 = s[6] - '0';
        }
        
        if (f < 0) m -= d2 * 6;
        if (f > 0) m += d2 * 6;
        if (m < 0) m += 60, h--;
        if (m >= 60) m -= 60, h++;

        if (f > 0) d = d-8;
        else if (f < 0) d = (-8)-d;

        h += d;
        if (h < 0) h += 24;
        if (h < 0) h += 24;
        if (h < 0) h += 24;
        if (h >= 24) h -= 24;
        if (h >= 24) h -= 24;
        if (h >= 24) h -= 24;
        
        if (h < 10) printf("0");
        printf("%d:", h);
        if (m < 10) printf("0");
        printf("%d\n", m);
    }
    // system("pause");
    return 0;
}