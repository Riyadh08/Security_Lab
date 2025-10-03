#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

int main() {
    // Define big integer type
    cpp_int big1, big2, result;

    // Assign very large values (beyond 64-bit)
    big1 = cpp_int("123456789123456789123456789123456789");
    big2 = cpp_int("987654321987654321987654321987654321");

    // Perform arithmetic operations
    result = big1 + big2;
    cout << "Addition: " << result << endl;

    result = big2 - big1;
    cout << "Subtraction: " << result << endl;

    result = big1 * big2;
    cout << "Multiplication: " << result << endl;

    result = big2 / big1;
    cout << "Division: " << result << endl;

    result = big2 % big1;
    cout << "Modulo: " << result << endl;

    // Power example (big exponentiation)
    result = pow(big1, 5);  // big1^5
    cout << "Power: " << result << endl;

    return 0;
}
