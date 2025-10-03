#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

// Modular exponentiation: (base^exp) % mod
cpp_int modExp(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    cpp_int base = cpp_int("123456789123456789123456789");
    cpp_int exp = cpp_int("987654321987654321");
    cpp_int mod = cpp_int("1000000007"); // prime modulus

    cpp_int ans = modExp(base, exp, mod);

    cout << "Result = " << ans << endl;
    return 0;
}
