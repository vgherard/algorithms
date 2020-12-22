// Compute the greatest commond divisor of two numbers

#include <iostream>

int gcd(int a, int b) {
    a = a % b;
    if (a == 0) return b;
    return gcd(b, a);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
