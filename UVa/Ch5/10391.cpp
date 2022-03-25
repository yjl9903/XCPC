#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;
typedef long long ll;
const int maxn = 120000 + 5;

vector<string> x;
set<string> s;
vector<int> vis;

int main(){
    string t;
    while (cin >> t)    x.push_back(t), s.insert(t), vis.push_back(0);
    sort(x.begin(), x.end());
    for (int i = 0; i < x.size(); i++){
        /* int flag = 1;
        for (int j = i + 1; flag; j++){
            //cout << x[j] << endl;
            for (int k = 0; k < x[i].length(); k++){
                if (k >= x[j].length() || x[i][k] != x[j][k]){
                    flag = 0;
                    break;
                }
            }
            if (flag){
                string t;
                for (int k = x[i].length(); k < x[j].length(); k++)
                    t.push_back(x[j][k]);
                //cout << x[i] << ' ' << t << endl;
                if (s.count(t) && !vis[j])
                    cout << x[j] << endl, vis[j] = 1; 
            }
        } */
        for (int j = 0; j < x[i].size(); j++){
            string t1, t2;
            t1 = x[i].substr(0, j);
            t2 = x[i].substr(j);
            //cout << t1 << ' ' << t2 << endl;
            if (s.count(t1) && s.count(t2)){
                cout << x[i] << endl;
                break;
            }
        }
    }
    return 0;
}