#include <iostream>
#include <cstring>
using namespace std;


int* partition(int* l, int* r){
    int x = *r;
    int *i = l - 1;
    for (int* j = l; j <= r - 1; j++){
        if (*j <= x){
            i++;
            int tmp = *i;
            *i = *j; *j = tmp;
        }
    }
    int tmp = *(i + 1); *(i + 1) = *r; *r = tmp;
    return i + 1;
}
void quicksort(int* l, int* r){
    if (l >= r) return;
    int* m = partition(l, r);
    quicksort(l, m - 1); quicksort(m + 1, r);
}

int main(){
    int n;
    while (cin >> n){
        int a[20];
        for (int i = 0; i < n; i++) cin >> a[i];
        quicksort(a, a + n - 1);
        for (int i = 0; i < n; i++) cout << a[i] << ' ';
        cout << endl;
    }
    return 0;
}