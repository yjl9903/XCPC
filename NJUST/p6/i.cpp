#include <iostream>
#include <cstring>
#include <ctime>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int n, m, a[maxn];
int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}

int main(){
    clock_t starttime, endtime;
    starttime = clock();
    int T; cin >> T;
    while (T--){
        cin >> n >> m; ms(a, -1);
        while (m--){
            int x, y; cin >> x >> y;
            a[x] = y;
        }
        int k = n;
        if (a[1] == -1) a[1] = 100; 
        if (a[2] == -1) a[2] = a[1];

        while (a[k] == -1 && k > 0) a[k] = 0, k--;
        for (int i = k - 1; i > 0; i--){
            if (a[i] == -1) a[i] = a[i + 1];
        }

        int sum = 0, t = a[1] + a[2];
        for (int i = 1; i <= n; i++) sum += a[i];
        int c = gcd(t, sum);
        cout << t / c << '/' << sum / c << endl;
        
    }

    endtime = clock();
	printf("\n\n %.3f s", double(endtime - starttime) / CLOCKS_PER_SEC);
    return 0;
}