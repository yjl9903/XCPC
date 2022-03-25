#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define N 2000010
const int p = 998244353;
char s[N], L[N], R[N];
ll sum[N];
 
struct ExKMP {
	int Next[N];
	int extend[N];
	//下标从1开始
	void get_Next(char *s) {
		int lens = strlen(s + 1), p = 1, pos;
		//Next[1]要特殊考虑
		Next[1] = lens;
		while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
		//Next[2]初始化
		Next[pos = 2] = p - 1;
		for (int i = 3; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			//第一种情况
			if (len + i < p + 1) Next[i] = len;
			//第二种情况
			else {
				//找到对于子串最靠后已经匹配的位置
				int j = max(p - i + 1, 0);
				//暴力匹配
				while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
				p = i + (Next[pos = i] = j) - 1; 
			}
		}
	}
 
	void work(char *s, char *t) {
		get_Next(t);
		int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
		while (p <= lent && s[p] == t[p]) ++p;
		p = extend[pos = 1] = p - 1;
		for (int i = 2; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			if (len + i < p + 1) extend[i] = len;
			else {
				int j = max(p - i + 1, 0);
				while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
				p = i + (extend[pos = i] = j) - 1;
			}
		}
	}
}exkmp[2]; 
 
template <class T1, class T2>
void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;
}
 
bool BigL(int l, int r) {
	int LCP = exkmp[0].extend[l];
	if (l + LCP - 1 >= r) return 1;
	return s[l + LCP] > L[1 + LCP];
}
 
bool SmallR(int l, int r) {
	int LCP = exkmp[1].extend[l];
	if (l + LCP - 1 >= r) return 1;
	return s[l + LCP] < R[1 + LCP];
}
 
int main() {
	while (scanf("%s%s%s", s + 1, L + 1, R + 1) != EOF) {
		int lens = strlen(s + 1), lenL = strlen(L + 1), lenR = strlen(R + 1);
		exkmp[0].work(s, L); exkmp[1].work(s, R);
		for (int i = 1; i <= lens; ++i) sum[i] = 0;
		ll res = 1;
		sum[1] = p - 1;
		for (int i = 1; i <= lens; ++i) {
			cout << i - 1 << ' ' << res << endl;
			int l, r;  
			if (s[i] == '0') {
				if (L[1] == '0') {
					l = r = i;
				} else {
					add(res, sum[i]);
					continue;
				}
			} else { 
				l = i + lenL - 1; if (!BigL(i, l)) ++l;
				r = i + lenR - 1; if (!SmallR(i, r)) --r;	
			}
			if (l <= r) {
				add(sum[l], res);
				add(sum[r + 1], p - res);
			}
			add(res, sum[i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}