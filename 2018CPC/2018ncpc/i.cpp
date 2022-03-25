#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

struct BigIntegar{
    static const int BASE = 1000;
    static const int WIDTH = 3;
    vector<int> s;

    BigIntegar(ll x = 0){ *this = x; }
    BigIntegar(const string& str){ *this = str; }
    BigIntegar operator = (ll x){
        s.clear();
        do{
            s.push_back(x % BASE);
            x /= BASE;
        }while (x > 0);
        return *this;
    }
    BigIntegar operator = (const string& str){
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++){
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }
    BigIntegar operator + (const BigIntegar& b) const {
        BigIntegar c; c.s.clear();
        for (int i = 0, g = 0; ; i++){
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = g;
            if (i < s.size()) x += s[i];
            if (i < b.s.size()) x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
    BigIntegar operator += (const BigIntegar& b){
        *this = *this + b; return *this;
    }
    bool operator < (const BigIntegar& b) const {
        if (s.size() != b.s.size()) return s.size() < b.s.size();
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
    bool operator <= (const BigIntegar& b) const {
        return !(b < *this);
    }
    bool operator == (const BigIntegar& b) const {
        return *this <= b && b <= *this;
    }
}s;
ostream& operator << (ostream& out, const BigIntegar& x){
    out << x.s.back();
    for (int i = x.s.size() - 2; i >= 0; i--){
        char buf[20];
        sprintf(buf, "%03d", x.s[i]);
        for (int j = 0; j < strlen(buf); j++) out << buf[j];
    }
    return out;
}
istream& operator >> (istream& in, BigIntegar& x){
    string str; cin >> str;
    x = str;
    return in;
}

struct node{
    BigIntegar x; int id;
    bool operator<(const node& b)const{
        return x < b.x;
    }
}a[maxn];
string tmp, str[maxn];
set<BigIntegar> st; 
int n, pre[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> tmp; s = BigIntegar(tmp);
    st.insert(0);
    for (int i = 0; i < n; i++){
        cin >> str[i] >> a[i].x;
        a[i].id = i; 
        // cout << a[i].x << endl;
    }
    sort(a, a + n);
    vector<int> ans; BigIntegar x(0);
    for (int i = n - 1; i >= 0; i--){
        BigIntegar t = x + a[i].x;
        if (t <= s){
            x += a[i].x; ans.push_back(a[i].id);
        }
    }
    if (x == s){
        cout << ans.size() << endl;
        for (int x : ans){
            cout << str[x] << endl;
        }
    }
    else cout << 0 << endl;
    return 0;
}