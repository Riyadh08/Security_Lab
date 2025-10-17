#include <iostream>
#include <cmath>
#include <numeric>   // for std::gcd
#include <iomanip>
using namespace std;

// Function to perform modular exponentiation
// (base^exp) % mod efficiently
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Big primes (for demonstration, large values truncated for simplicity)
    long long p = 8148581513988253039LL;
    long long q = 8117199308616590384LL;

    long long n = p * q;
    long long fi_n = (p - 1) * (q - 1);

    long long message = 9876543210LL;
    cout << "Message: " << message << endl;

    // Find public exponent e
    long long e;
    for (long long i = 2; i < fi_n; i++) {
        if (gcd(i, fi_n) == 1) {
            e = i;
            break;
        }
    }
    cout << "Public exponent (e): " << e << endl;

    // Find private key d
    long long d = 0;
    for (long long k = 1; k < 150; k++) {
        long long x = 1 + k * fi_n;
        if (x % e == 0) {
            d = x / e;
            break;
        }
    }
    cout << "Private exponent (d): " << d << endl;

    // Signing: signature = message^d mod n
    long long signature = modExp(message, d, n);
    cout << "Signature: " << signature << endl;

    // Verification: verified = signature^e mod n
    long long verified = modExp(signature, e, n);
    cout << "Verification result: " << verified << endl;

    if (verified == message)
        cout << "✅ Signature is valid!" << endl;
    else
        cout << "❌ Signature is invalid!" << endl;

    return 0;
}
