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

struct Node {
    string name;
    vector<int> card;
    int type, v1, v2, v3;
    Node() {}
    Node(string name, string cards) {
        this->name = name;
        for (int i = 0; i < (int)cards.length(); i++) {
            if (cards[i] == 'A') {
                card.push_back(1);
            } else if (cards[i] == '1') {
                i++;
                card.push_back(10);
            } else if (cards[i] == 'J') {
                card.push_back(11);
            } else if (cards[i] == 'Q') {
                card.push_back(12);
            } else if (cards[i] == 'K') {
                card.push_back(13);
            } else {
                card.push_back(cards[i] - '0');
            }
        }
        // cout << name << endl;
        // for (int x: card) cout << x << ' ';
        // cout << endl;
        vector<int> vis(15, 0);
        int sum = 0;
        for (int x: card) {
            vis[x]++; sum += x;
        }
        if (vis[10] && vis[11] && vis[12] && vis[13] && vis[1]) {
            type = 1; return ;
        }
        for (int i = 1; i + 4 <= 13; i++) {
            if (vis[i] && vis[i + 1] && vis[i + 2] && vis[i + 3] && vis[i + 4]) {
                type = 2; v1 = i + 4; return ;
            }
        }
        int two = 0, three = 0, four = 0;
        for (int i = 1; i <= 13; i++) {
            if (vis[i] == 2) {
                two++;
            } else if (vis[i] == 3) {
                three++;
            } else if (vis[i] == 4) {
                four++;
            }
        }
        if (four) {
            type = 3;
            for (int i = 1; i <= 13; i++) {
                if (vis[i] == 4) {
                    v1 = i;
                }
            }
            v2 = sum - 4 * v1;
        } else if (three && two) {
            type = 4;
            for (int i = 1; i <= 13; i++) {
                if (vis[i] == 3) {
                    v1 = i;
                } else if (vis[i] == 2) {
                    v2 = i;
                }
            }
        } else if (three) {
            type = 5;
            for (int i = 1; i <= 13; i++) {
                if (vis[i] == 3) {
                    v1 = i;
                    v2 = sum - v1 * 3;
                }
            }
        } else if (two == 2) {
            type = 6;
            v1 = v2 = -1;
            for (int i = 1; i <= 13; i++) {
                if (vis[i] == 2) {
                    if (v1 == -1) v1 = i;
                    else v2 = i;
                }
            }
            if (v1 < v2) swap(v1, v2);
            v3 = sum - 2 * v1 - 2 * v2;
        } else if (two == 1) {
            type = 7;
            for (int i = 1; i <= 13; i++) {
                if (vis[i] == 2) {
                    v1 = i;
                    v2 = sum - v1 * 2;
                }
            }
        } else {
            type = 8;
            v1 = sum;
        }
    }

    bool operator<(const Node& b) const {
        if (type != b.type) return type < b.type;
        if (type == 1) {

        } else if (type == 2) {
            if (v1 != b.v1) return v1 > b.v1;
        } else if (type == 3) {
            if (v1 != b.v1) return v1 > b.v1;
            if (v2 != b.v2) return v2 > b.v2;
        } else if (type == 4) {
            if (v1 != b.v1) return v1 > b.v1;
            if (v2 != b.v2) return v2 > b.v2;
        } else if (type == 5) {
            if (v1 != b.v1) return v1 > b.v1;
            if (v2 != b.v2) return v2 > b.v2;
        } else if (type == 6) {
            if (v1 != b.v1) return v1 > b.v1;
            if (v2 != b.v2) return v2 > b.v2;
            if (v3 != b.v3) return v3 > b.v3;            
        } else if (type == 7) {
            if (v1 != b.v1) return v1 > b.v1;
            if (v2 != b.v2) return v2 > b.v2;
        } else if (type == 8) {
            if (v1 != b.v1) return v1 > b.v1;
        }
        return name < b.name;
    }
};

int n;

int main() {
    while (scanf("%d", &n) == 1) {
        char s[20], t[20];
        vector<Node> v;
        for (int i = 1; i <= n; i++) {
            scanf("%s%s", s, t);
            v.push_back((Node){string(s), string(t)});
        }
        sort(v.begin(), v.end());
        for (auto& x: v) {
            printf("%s\n", x.name.c_str());
        }
    }
    return 0;
}