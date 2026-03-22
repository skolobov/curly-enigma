#ifndef NUMOPS_NUMOPS_H
#define NUMOPS_NUMOPS_H

namespace numops {

/// Returns the sum of two integers.
int add(int a, int b);

/// Returns the difference of two integers (a - b).
int subtract(int a, int b);

/// Returns the product of two integers.
int multiply(int a, int b);

/// Returns the result of integer division (a / b).
/// If b is zero, returns 0.
int divide(int a, int b);

/// Returns the absolute value of an integer.
/// For INT_MIN, returns INT_MAX (saturating behavior).
int abs(int a);

}  // namespace numops

#endif  // NUMOPS_NUMOPS_H
