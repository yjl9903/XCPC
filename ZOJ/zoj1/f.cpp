#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

struct LinearBase {
    static const int max_log = 30;
    int a[max_log];
    bool zero;
    int cnt;
    LinearBase() { cnt = 0; zero = false; ms(a,0); }
    void insert(int x) {
        for (int i = max_log - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i]) x ^= a[i];
                else {
                    cnt++;
                    a[i] = x;
                    return;
                }
            }
        }
    }
};

int main(){
    
    return 0;
}