#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

struct BigIntegar
{
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
    BigIntegar operator * (const BigIntegar& b){
        BigIntegar c, t; c.s.clear(); t.s.clear();
        for (int i = 0; i < s.size(); i++){
            BigIntegar x = t;
            for (int j = 0; j < b.s.size(); j++){
                x.s.push_back(s[i] * b.s[j]);
            }
            int g = 0;;
            for (int j = 0; j < b.s.size(); j++){
               x.s[i + j] += g;
               g = x.s[i + j] / BASE;
               x.s[i + j] %= BASE;
            }
            if (g) x.s.push_back(g);
            c += x;
            t.s.push_back(0);
        }
        return c;
    }
    bool operator < (const BigIntegar& b) const {
        if (s.size() != b.s.size()) return s.size() < b.s.size();
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
    bool operator > (const BigIntegar& b) const {
        return b < *this;
    }
    bool operator == (const BigIntegar& b) const {
        
    }
    bool operator != (const BigIntegar& b) const {

    }
};
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

int main(){
    // string x1("12345678987654321"), y1("98765432123456789");
    string x1("12345678"), y1("12345678");
    // BigIntegar x, y;
    BigIntegar x = x1, y = y1;
    cout << x * y << endl;
    while (cin >> x >> y){
        cout << x * y << endl;
    }
    system("pause");
    return 0;
}