#include <iostream>
#include <cstring>
using namespace std;

int b[20];

void mergesort(int* l, int* r){
    if (l >= r) return;
    int* m = l + (r - l) / 2;
    mergesort(l, m); mergesort(m + 1, r);
    int* i = l, * j = m + 1, k = 0;
    while (i <= m && j <= r){
        if (*i > *j) *(b + k) = *j, j++;
        else *(b + k) = *i, i++; 
        k++;
    }
    while (i <= m) *(b + k) = *i, k++, i++;
    while (j <= r) *(b + k) = *j, k++, j++;
    for (int* i = l, k = 0; i <= r; i++, k++) *i = *(b + k);
}

int main(){
    int n;
    while (cin >> n){
        int a[20];
        for (int i = 0; i < n; i++) cin >> a[i];
        mergesort(a, a + n - 1);
        for (int i = 0; i < n; i++) cout << a[i] << ' ';
        cout << endl;
    }
    return 0;
}