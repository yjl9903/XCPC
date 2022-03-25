#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const double pi = acos(-1.0);

int a, b;
char s[100];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &a, &b);
        double res = 2.0 * b + pi * a;
        sprintf(s, "%.7lf", res);
        int len = strlen(s); s[len - 1] = '\0';
        printf("%s\n", s);
        // printf("%.6lf\n", res);
    }
    return 0;
}