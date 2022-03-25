#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int mod = 1e9 + 7;

int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}
struct point{
    int x, y; 
    point (int x = 0, int y = 0): x(x), y(y){}
    point operator + (const point& b){return point(x + b.x, y + b.y);}
    point operator - (const point& b){return point(x - b.x, y - b.y);}
}p[maxn];
double cross(const point& a, const point& b){return a.x * b.y - a.y * b.x;}
bool operator < (const point& a, const point& b){return a.x < b.x || (a.x == b.x && a.y < b.y);}

map<point, int> mp;
int n;
ll f[maxn];

int main(){
    f[0] = 1; for (int i = 1; i < maxn; i++) f[i] = f[i - 1] * 2 % mod;
    int T; cin >> T;
    while (T--){
        cin >> n; ll res = 0;
        for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
        sort(p, p + n);  
        
        for (int i = 0; i < n; i++){
            int len = 1; mp.clear();
            for (int j = i + 1; j < n; j++){
                if (p[i].x == p[j].x && p[i].y == p[j].y){
                    len++; continue;
                }
                int xx = p[i].x - p[j].x, yy = p[i].y - p[j].y, k = gcd(xx, yy);
                if (k != 0){
                    xx /= k, yy /= k;
                }
                mp[point(xx, yy)]++;
            }
            if (len > 1){res += f[len - 1] - 1; res %= mod;}
            for (map<point,int>::iterator it = mp.begin(); it != mp.end(); it++){
                int t = it -> second;
                res += f[len - 1] * (f[t] - 1);
                res %= mod;
            }
        }
        cout << res << endl;
    }
    return 0;
}