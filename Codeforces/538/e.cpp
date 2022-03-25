#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 1000000 + 5;

int rand(){
    static int seed = 233333;
    return seed = int(seed * 482711ll % 2147483647);
}
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }

int n, a[maxn];

int main() {
    // srand(time(NULL)); srand(rand()); srand(rand()); srand(rand()); srand(rand());
    cin >> n;
    if (n <= 60) {
        vector<int> v;
        for (int i = 1; i <= n; i++) {
            cout << "? " << i << endl;
            int x; cin >> x; v.push_back(x);
        }
        sort(v.begin(), v.end());
        cout << "! " << v[0] << ' ' << (v.back() - v.front()) / (n - 1) << endl;
        return 0;
    }
    int l = 0, r = 1e9, mx = 0, c = 0;
    while (l <= r) {
        c++;
        int m = (l + r) >> 1, x;
        cout << "> " << m << endl; cin >> x;
        if (x == 0) r = m - 1, mx = m;
        else l = m + 1;
    }
    // cout << mx << endl;
    // int g = 0;
    for (int i = 0; i < n; i++) a[i] = i + 1;
    mt19937 rnd(time(NULL));
    shuffle(a, a + n, rnd);
    vector<int> v; 
    for (int i = 1, x; i <= 30; i++) {
        cout << "? " << a[i] << endl; cin >> x;
        v.push_back(x);
        // if (g == 0) g = mx - x;
        // else g = gcd(g, mx - x);
    }
    sort(v.begin(), v.end()); 
    int g = v[1] - v[0];
    for (int i = 1; i < v.size(); i++) {
        g = gcd(v[i] - v[i - 1], g);
        assert(v[i] != v[i - 1]);
    }

    cout << "! " << mx - g * (n - 1) << ' ' << g << endl;
    return 0;
}