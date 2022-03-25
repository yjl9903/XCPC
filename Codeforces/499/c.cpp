#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int n, m;
PII a[maxn];
bool cmp(PII a, PII b){
    double x1 = double(a.first + a.second - 1) / double(a.first * a.second);
    double x2 = double(b.first + b.second - 1) / double(b.first * b.second);
    return x1 < x2;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i].first);
    for (int i = 0; i < n; i++) scanf("%d", &a[i].second);
    sort(a + 1, a + n, cmp);
    double res = 0;
    int flag = 0;
    if (a[0].second <= 1) flag = 1;
    else {
        res = double(m) / double(a[0].second - 1);
    }
    for (int i = n - 1; i > 0; i--){
        if (a[i].second <= 1 || a[i].first <= 1) {
            flag = 1; break;
        }
        double k = double(a[i].first * a[i].second) / double(a[i].first * a[i].second - a[i].first - a[i].second + 1);
        res = k * (res + 1.0 * m) - 1.0 * m;
    }
    if (a[0].first <= 1) flag = 1;
    else {
        res = (1.0 * m + a[0].first * res) / double(a[0].first - 1);
    }

    if (flag) printf("-1");
    else printf("%.7lf", res);
    return 0;
}