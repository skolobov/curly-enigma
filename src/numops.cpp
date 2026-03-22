#include <numops/numops.h>

#include <climits>

namespace numops {

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int divide(int a, int b) { return b == 0 ? 0 : a / b; }

int abs(int a) {
    if (a == INT_MIN) return INT_MAX;
    return a < 0 ? -a : a;
}

}  // namespace numops
