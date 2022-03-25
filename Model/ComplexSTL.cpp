#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

typedef complex<double> Point;
typedef Point Vector;

double dot(Vector a, Vector b){ return real(conj(a) * b); }
double cross(Vector a, Vector b){ return imag(conj(a) * b); }
Vector rotate(Vector a, double rad){ return a * conj(Point(0, rad)); }

int main(){

    return 0;
}