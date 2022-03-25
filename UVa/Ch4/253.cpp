#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
#define PCC pair<char,char>

char src[20], tag[10];
PCC x[3], y[3];

bool solve(){
    for (int i = 0; i < 4; i++){
        swap(y[0], y[1]);
        swap(y[1].first, y[1].second);
        for (int j = 0; j < 4; j++){
            swap(y[0], y[2]);
            swap(y[2].first, y[2].second);
            for (int k = 0; k < 4; k++){
                swap(y[1], y[2]);
                swap(y[2].first, y[2].second);
                int flag = 1;
                for (int i = 0; i < 3; i++)
                    if (x[i] != y[i])
                        flag = 0;
                if (flag)   return true;
            }
        }
    }
    return false;
}

int main(){
    while (cin >> src){
        for (int i = 0; i < 3; i++){
            x[i].first = src[i];
            x[i].second = src[5 - i];
            y[i].first = src[i + 6];
            y[i].second = src[11 - i];
        }
        cout << (solve() ? "TRUE" : "FALSE") << endl;
    }
    return 0;
}