#include <numops/numops.h>

#include <cstdlib>
#include <iostream>

int main() {
    int result = 0;

    if (numops::add(2, 3) != 5) {
        std::cerr << "FAIL: add(2, 3) != 5\n";
        result = EXIT_FAILURE;
    }

    if (numops::subtract(10, 4) != 6) {
        std::cerr << "FAIL: subtract(10, 4) != 6\n";
        result = EXIT_FAILURE;
    }

    if (numops::multiply(3, 7) != 21) {
        std::cerr << "FAIL: multiply(3, 7) != 21\n";
        result = EXIT_FAILURE;
    }

    if (numops::divide(10, 3) != 3) {
        std::cerr << "FAIL: divide(10, 3) != 3\n";
        result = EXIT_FAILURE;
    }

    if (numops::abs(-7) != 7) {
        std::cerr << "FAIL: abs(-7) != 7\n";
        result = EXIT_FAILURE;
    }

    if (result == 0) {
        std::cout << "numops integration test: all checks passed\n";
    }

    return result;
}
