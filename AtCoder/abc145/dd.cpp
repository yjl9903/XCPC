#include <bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
const int C = 5032107 + 1;
int lp[C];
int fred[C];
int num_primes[C];

void relax_max(int& x, int y) {
  if (y > x) x = y;
}

const int MAX_DIVISORS = 7;
const int MAX_ANS = 2 * MAX_DIVISORS;

int max_left[MAX_DIVISORS + 1][C];
int max_border[MAX_ANS + 1];

vector<int> cur_primes;

vector<int> divs;

void get_divisors(int n) {
    divs = {1};
    while (n > 1) {
        int p = lp[n];
        n /= p;
        int sz = divs.size();
        for (int i = 0; i < sz; ++i) {
            divs.push_back(divs[i] * p);
        }
    }
}

void solve(bool read) {
    vector<int> pr;
    for (int i = 2; i < C; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] < C; ++j) {
            lp[i * pr[j]] = pr[j];
        }
    }
    fred[1] = 1;
    for (int i = 2; i < C; ++i) {
        int p = lp[i];
        int cur = i / p;
        if (cur % p == 0) {
            fred[i] = fred[cur / p];
            num_primes[i] = num_primes[cur / p];
        } else {
            fred[i] = p * fred[cur];
            num_primes[i] = num_primes[cur] + 1;
        }
    }

    for (int i = 0; i < C; ++i) {
        for (int j = 0; j <= MAX_DIVISORS; ++j) {
            max_left[j][i] = -1;
        }
    }
    memset(max_border, -1, sizeof(max_border));

    int n;
    cin >> n;
    int Q;
    cin >> Q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] = fred[a[i]];
    }

    vector<vector<pair<int, int>>> queries(n);

    vector<int> res(Q);
    for (int i = 0; i < Q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        queries[r].push_back({l, i});
    }

    for (int i = 0; i < n; ++i) {
        get_divisors(a[i]);
        dbg(a[i]);
        for (int d : divs) {
          dbg(d);
            int first_add = num_primes[a[i]] - num_primes[d];
            for (int prev_ans = 0; prev_ans <= MAX_DIVISORS; ++prev_ans) {
                int cur_left = max_left[prev_ans][d];
                int cur_ans = first_add + prev_ans;
                if (cur_ans <= MAX_ANS) {
                    relax_max(max_border[cur_ans], cur_left);
                }
            }
        }
        for (int d : divs) {
            int first_add = num_primes[a[i]] - num_primes[d];
            relax_max(max_left[first_add][d], i);
        }
        for (auto q : queries[i]) {
            res[q.second] = MAX_ANS + 1;
            for (int cur_ans = 0; cur_ans <= MAX_ANS; ++cur_ans) {
                if (max_border[cur_ans] >= q.first) {
                    res[q.second] = cur_ans;
                    break;
                }
            }
            assert(res[q.second] <= MAX_ANS);
        }
    }

    int sum_ans = 0;
    for (int i = 0; i < Q; ++i) {
        cout << res[i] << '\n';
    }
}

int main() {
  solve(1);
  return 0;
}