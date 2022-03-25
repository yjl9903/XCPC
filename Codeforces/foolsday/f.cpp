#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

string s;
bool f[26] = {1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1};

int main() {
    cin >> s;
    // if (s == "NEAT" || s == "AI" || s == "JUROR") puts("YES");
    // else puts("NO");
    int sum = 0;
    for (int i = 0; i < s.length(); i++) {
        sum += f[s[i] - 'A'];
    }
    // cout <<sum << endl;
    if (sum == 0 || sum == (int)s.length()) puts("YES");
    else puts("NO");
    return 0;
}

/*
Neat Words

NEAT
AI
JUROR

WORD
CODER
APRILFOOL
YES
*/