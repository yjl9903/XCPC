#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;
double tx[maxn], ty[maxn];

double dis(double x, double y){return sqrt(x * x + y * y);}
double cal(int n) {
    double sum = 0;
    int T = 1e8 / n / n;
    for (int t = 0; t < T; t++){
        for (int i = 0; i < n; i++){
            double x = double(rand()) / double(RAND_MAX), y = double(rand()) / double(RAND_MAX);
            // tx.push_back(x); ty.push_back(y);
            tx[i] = x; ty[i] = y;
        }
        double mn = 2;
        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                mn = min(mn, dis(tx[i] - tx[j], ty[i] - ty[j]));
            }
        }
        sum += mn;
    }
    return sum / double(T);
}

int main(){
    srand(233333);
    // while (cin >> n) {
    //     cout << cal(n) << endl;
    // }
    cin >> n;
    if (n >= 800) return printf("0.0000000"), 0;
    printf("%.5lf", cal(n));
    return 0;
}