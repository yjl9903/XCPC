#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;



int main() {
  string s; cin >> s;
  if (s == "SUN") puts("7");
  else if (s == "MON") puts("6");
  else if (s == "TUE") puts("5");
  else if (s == "WED") puts("4");
  else if (s == "THU") puts("3");
  else if (s == "FRI") puts("2");
  else if (s == "SAT") puts("1");
  return 0;
}