struct B {};

struct A {
  B f;
};

int main() {
  A a = new A();
  B b = new B();
  a.f = b;
  // A = b; ???
}