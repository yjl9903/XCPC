#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int inverse(int a, int m) {
    a %= m;
    if (a < 0) {
        a += m;
    }
    int b = m, u = 0, v = 1;
    while (a) {
        int t = b / a;
        b -= a * t;
        swap(a, b);
        u -= v * t;
        swap(u, v);
    }
    if (u < 0) {
        u += m;
    }
    return u;
}

template <int P>
struct ModNum {
  static constexpr int mod = P;

  int v;
 
  ModNum(): v(0) { }

  ModNum(ll vv) {
    v = vv % mod;
    if (v < 0) v += mod;
  }
 
  explicit operator int() const {
    return v;
  }
 
  bool operator==(const ModNum& b) const {
    return v == b.v;
  }

  bool operator!=(const ModNum& b) const {
    return v != b.v;
  }
 
  ModNum inverse() const {
    return ModNum(::inverse(v, mod));
  }
 
  ModNum operator-() const {
    return ModNum(v ? mod - v : 0);
  }
  
  ModNum operator+() const {
    return *this;
  }
 
  ModNum& operator++() {
    v++; if (v == mod) v = 0;
    return *this;
  }
  
  ModNum& operator--() {
    if (v == 0) v = mod;
    v--; return *this;
  }
 
  ModNum operator++(int) {
    ModNum r = *this;
    ++*this; return r;
  }
  
  ModNum operator--(int) {
    ModNum r = *this;
    --*this; return r;
  }
 
  ModNum& operator+=(const ModNum& b) {
    v += b.v;
    if (v >= mod) v -= mod;
    return *this;
  }
 
  ModNum operator+(const ModNum& b) const {
    return ModNum(*this) += b;
  }
 
  ModNum& operator-=(const ModNum& b) {
    v -= b.v;
    if (v < 0) v += mod;
    return *this;
  }
 
  ModNum operator-(const ModNum& b) const {
    return ModNum(*this) -= b;
  }
 
  ModNum& operator*=(const ModNum& b) {
    v = (int)(1ll * v * b.v % P);
    return *this;
  }
 
  ModNum operator*(const ModNum& b) const {
    return ModNum(*this) *= b;
  }
  
  ModNum& operator/=(const ModNum& b) {
    return *this *= b.inverse();
  }
 
  ModNum operator/(const ModNum& b) const {
    return ModNum(*this) /= b;
  }
};
 
template <int P>
ostream& operator<<(ostream& out, const ModNum<P>& n) {
  return out << int(n);
}
 
template <int P>
istream& operator>>(istream& in, ModNum<P>& n) {
  long long v; in >> v;
  n = ModNum<P>(v);
  return in;
}

int main() {
    
    return 0;
}