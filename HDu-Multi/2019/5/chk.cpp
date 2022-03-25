#include <bits/stdc++.h>
#include <testlib.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;



int main (int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for (int t = 1; t <= T; t++) {
        int n = inf.readInt();
        for (int i = 1, x; i <= n; i++) x = inf.readInt();
        int f = ans.readInt(), g = ouf.readInt();
        if (f == -1) {
            if (g != -1) quitf(_wa, "wrong impossible case");
        } else {
            if (f != g) quitf(_wa, "wrong answer on test %d, %d", t, 1);
            for (int i = 2; i <= 2 * n; i++) {
                f = ans.readInt();
                g = ans.readInt();
                if (f != g) quitf(_wa, "wrong answer on test %d, %d", t, i);
            }
        }
    }
    quitf(_ok, "accepted");
}