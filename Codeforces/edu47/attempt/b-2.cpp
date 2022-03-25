#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define ll long long

using namespace std;

const int N = (int)1e5 + 10;
int n; char s[N];


int main(){

	scanf("%s", s + 1);
	n = strlen(s + 1);

	int cnt = 0;
	for (int i = 1; i <= n; i ++)
		if (s[i] == '1') cnt ++;

	bool find = false;
	for (int i = 1; i <= n; i ++){
		if (s[i] == '2'){
			if (!find){
				find = true;
				for (int j = 1; j <= cnt; j ++)
					putchar('1');
			}
		}
		if (s[i] != '1')
			putchar(s[i]);
	}

	if (!find){
		for (int j = 1; j <= cnt; j ++)
			putchar('1');
	
	}
	
	return 0;
}