#include <bits/stdc++.h>
using Hash = uint64_t;
const Hash MAGIC = 1e6 + 3;
const int maxn = 1e5 + 5;

Hash power[maxn];

int n, a[maxn], next[maxn], order[maxn], event[maxn];

struct Solver {
  int n, bsize;
  std::vector<std::vector<Hash *>> hashes;
  std::vector<std::vector<Hash>> blocks;

  Solver(int n)
      : n(n), bsize(get_sqrt(n)),
        hashes(n + 1, std::vector<Hash *>(bsize)) {
    std::string str;
    std::cin >> str;
    for (int i = 0; i < n; ++i) {
      event[i] = -1;
      a[i] = str[i] - 'a';
    }

    blocks.emplace_back(bsize + 1);
    for (int i = 0; i < bsize; ++i) {
      hashes[n][i] = blocks.back().data();
    }
    {
      blocks.emplace_back(bsize + 1);
      auto block = blocks.back().data();
      block[n % bsize] = -1;
      for (int i = bsize - 1; i >= 0; --i) {
        block[i] += block[i + 1] * MAGIC;
      }
      hashes[n][n / bsize] = block;
    }
    {
      // std::vector<int> next(n + 1, n);
      for (int i = 0; i <= n; i++) {
        next[i] = n;
      }
      for (int i = n - 1; i >= 0; --i) {
        hashes[i] = hashes[i + 1];
        int j = next[a[i]];
        next[a[i]] = i;
        if (j < n) {
          event[j] = i;
          blocks.emplace_back(bsize + 1);
          int block_id = j / bsize;
          int base = block_id * bsize;
          auto block = blocks.back().data();
          Hash hh = 0;
          for (int k = bsize - 1; k >= 0; --k) {
            hh = hh * MAGIC + char_at(i, base + k);
            block[k] = hh;
          }
          hashes[i][block_id] = block;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      order[i] = i;
    }
    std::sort(order, order + n, [this](int x, int y) {
      int length = get_lcp(x, y);
      return char_at(x, x + length) < char_at(y, y + length);
    });
    for (int i = 0; i < n; i++) {
      std::cout << order[i] + 1 << ' ';
    }
    std::cout << '\n';
  }

  static inline int get_sqrt(int n) {
    int b = 0;
    while (b * b <= n) {
      b++;
    }
    return b;
  }

  int char_at(int s, int i) const {
    if (i >= n) {
      return -1;
    }
    return s <= event[i] ? i - event[i] : 0;
  }

  int get_LCP(int x, int y) const {
    if (x == y) {
      return n - x;
    }
    int length = 0;
    while (char_at(x, x + length) == char_at(y, y + length)) {
      length++;
    }
    return length;
  }

  int get_lcp(int x, int y) const {
    int length = 0;
    if (x % bsize > y % bsize) {
      std::swap(x, y);
    }
    auto &hashx = hashes[x];
    auto &hashy = hashes[y];
    int xi = x / bsize;
    int yi = y / bsize;
    int xr = x % bsize;
    int yr = y % bsize;
    if (xr == yr) {
      if (hashx[xi][xr] == hashy[yi][yr]) {
        length += bsize - xr;
        xi++, yi++;
        xr = yr = 0;
        while (hashx[xi][0] == hashy[yi][0]) {
          xi++, yi++;
          length += bsize;
        }
      }
    } else {
      while (true) {
        if (hashx[xi][xr] - power[bsize - yr] * hashx[xi][xr + bsize - yr] ==
            hashy[yi][yr]) {
          xr += bsize - yr;
          length += bsize - yr;
          yi++, yr = 0;
        } else {
          break;
        }
        if (hashy[yi][yr] - power[bsize - xr] * hashy[yi][yr + bsize - xr] ==
            hashx[xi][xr]) {
          yr += bsize - xr;
          length += bsize - xr;
          xi++, xr = 0;
        } else {
          break;
        }
      }
    }
    int xx = xi * bsize + xr;
    int yy = yi * bsize + yr;
    while (char_at(x, xx) == char_at(y, yy)) {
      xx++, yy++, length++;
    }
    return length;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  power[0] = 1;
  for (int i = 1; i < maxn; ++i) {
    power[i] = power[i - 1] * MAGIC;
  }
  while (std::cin >> n) {
    Solver{n};
  }
}
