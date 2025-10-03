#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

using BigInt = cpp_int;

// Modular exponentiation for BigInt
BigInt modExp(BigInt base, BigInt exp, BigInt mod) {
    BigInt res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// Modular inverse using Fermat's little theorem (for prime modulus)
BigInt modInverse(BigInt a, BigInt p) {
    // a^(p-2) mod p
    return modExp(a, p - 2, p);
}

int main() {
    // -------------------------
    // Large prime example
    // -------------------------
    BigInt p("100000000000000000039"); // large prime (for demo)
    BigInt g = 5;
    BigInt a = 123456789; // private key
    BigInt y = modExp(g, a, p); // public key y = g^a % p

    cout << "Public Keys: (p,g,y): " << p << " " << g << " " << y << endl;
    cout << "Private Key: a = " << a << endl;

    // -------------------------
    // Encryption
    // -------------------------
    BigInt m = 987654321; // message
    BigInt k = 111111;    // random secret integer

    BigInt c1 = modExp(g, k, p);
    BigInt c2 = (m * modExp(y, k, p)) % p;

    cout << "Ciphertext: " << c1 << " " << c2 << endl;

    // -------------------------
    // Decryption
    // -------------------------
    BigInt s = modExp(c1, a, p);
    BigInt s_inv = modInverse(s, p);
    BigInt dec = (c2 * s_inv) % p;

    cout << "Decrypted message: " << dec << endl;

    return 0;
}
