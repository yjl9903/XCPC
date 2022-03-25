#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;

int mp[5][5], vis[5][5];

map<int,int> f {
  { 6, 10000 },
  { 7, 36 },
  { 8, 720 },
  { 9, 360 },
  { 10, 80 },
  { 11, 252 },
  { 12, 108 },
  { 13, 72 },
  { 14, 54 },
  { 15, 180 },
  { 16, 72 },
  { 17, 180 },
  { 18, 119 },
  { 19, 36 },
  { 20, 306 },
  { 21, 1080 },
  { 22, 144 },
  { 23, 1800 },
  { 24, 3600 },
};

int main() {
  set<int> st;
  for (int i = 1; i <= 9; i++) st.insert(i);
  int kx, ky;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      scanf("%d", &mp[i][j]);
      if (mp[i][j]) {
        st.erase(mp[i][j]);
      } else {
        kx = i;
        ky = j;
        vis[i][j] = 1;
      }
    }
  }
  assert(st.size() == 1);
  mp[kx][ky] = *st.begin();
  for (int i = 0; i < 3; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    vis[x][y] = 1;
    printf("%d\n", mp[x][y]);
  }
  int op;
  scanf("%d", &op);
  bool fi = true;
  int sum = 0;
  auto output = [&](int x, int y) {
    sum += mp[x][y];
    // vis[x][y] = 1;
    // if (vis[x][y]) {
    //   if (!fi) putchar('\n');
    //   printf("%d", mp[x][y]);
    //   fi = false;
    // }
  };
  if (op <= 3) {
    output(op, 1);
    output(op, 2);
    output(op, 3);
    printf("%d\n", f[sum]);
  } else if (op <= 6) {
    output(1, op - 3);
    output(2, op - 3);
    output(3, op - 3);
    printf("%d\n", f[sum]);
  } else if (op == 7) {
    output(1, 1);
    output(2, 2);
    output(3, 3); 
    printf("%d\n", f[sum]);
  } else if (op == 8) {
    output(3, 1);
    output(2, 2);
    output(1, 3);
    printf("%d\n", f[sum]);
  }
  return 0;
}