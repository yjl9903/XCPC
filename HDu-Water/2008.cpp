#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;
const double eps = 1e-8;

double a[maxn];
int n;

int dcmp(double x){if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;}

int main(){
    while (cin >> n && n){
        for (int i = 0; i < n; cin >> a[i++]);
        int s[3] = {0};
        for (int i = 0; i < n; i++){
            // cout << dcmp(a[i]) << ' ';
            s[dcmp(a[i]) + 1]++;
        }
        // cout << endl;
        cout << s[0] << ' ' << s[1] << ' ' << s[2] << endl;
    }
    return 0;
}