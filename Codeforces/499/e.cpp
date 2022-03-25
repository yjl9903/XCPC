#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, k;
int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
vector<int> v;

int main(){
    scanf("%d%d", &n, &k);
    int g = k;
    for (int i = 0, x; i < n; i++) scanf("%d", &x), g = gcd(g, x);
    for (int i = 0; i < k; i += g) v.push_back(i);
    printf("%d\n", v.size());
    for (int i = 0; i < v.size(); i++){
        if (i) putchar(' ');
        printf("%d", v[i]);
    }
    return 0;
}