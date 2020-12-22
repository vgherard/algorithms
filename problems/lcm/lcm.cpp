// Compute the least common multiple of two numbers

#include <iostream>

long long gcd(long long a, long long b) {
    a = a % b;
    if (a == 0) return b;
    return gcd(b, a);
}

long long lcm(long long a, long long b) {
  return a * b / gcd(a, b);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
