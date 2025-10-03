#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
using namespace std;
using namespace boost::multiprecision;

// Alias for big integer
using BigInt = cpp_int;

// Modular inverse using Extended Euclidean Algorithm
BigInt modInverse(BigInt a, BigInt m) {
    BigInt m0 = m;
    BigInt x = 1, y = 0;

    if (m == 1) return 0;

    while (a > 1) {
        BigInt q = a / m;       // quotient
        BigInt rem = a % m; // remainder

        BigInt old_a = a;
        BigInt old_y = y;

        a = m;
        m = rem;

        y = x - q * y;
        x = old_y;
    }

    if (x < 0) x += m0;
    return x;
}


// Key generation: returns {private x, public y}
pair<BigInt, BigInt> keyGen(BigInt p, BigInt g) {
    boost::random::mt19937 gen((unsigned)time(0));
    boost::random::uniform_int_distribution<long long> dist(2, 1e9);

    BigInt x = dist(gen);   // private key
    BigInt y = powm(g, x, p); // public key
    return {x, y};
}

// Encryption: returns {c1, c2}
pair<BigInt, BigInt> encrypt(BigInt m, BigInt p, BigInt g, BigInt y) {
    boost::random::mt19937 gen((unsigned)time(0));
    boost::random::uniform_int_distribution<long long> dist(2, 1e9);

    BigInt k = dist(gen);
    BigInt c1 = powm(g, k, p);
    BigInt c2 = (m * powm(y, k, p)) % p;
    return {c1, c2};
}

// Decryption
BigInt decrypt(BigInt c1, BigInt c2, BigInt p, BigInt x) {
    BigInt s = powm(c1, x, p);
    BigInt sInv = modInverse(s, p);
    return (c2 * sInv) % p;
}

// Demo
int main() {
    // Example large prime (keep it smaller for demo speed)
    BigInt p("1000000000000035000061");  
    BigInt g = 2; // primitive root for many primes

    cout << "Prime p = " << p << endl;
    cout << "Generator g = " << g << endl;

    // Key generation
    auto keys = keyGen(p, g);
    BigInt x = keys.first;  // private key
    BigInt y = keys.second; // public key

    cout << "Private key x = " << x << endl;
    cout << "Public key y = " << y << endl;

    // Message
    BigInt m("1188098");
    cout << "Original message m = " << m << endl;

    // Encrypt
    auto ct = encrypt(m, p, g, y);
    cout << "Ciphertext: c1 = " << ct.first << ", c2 = " << ct.second << endl;

    // Decrypt
    BigInt rm = decrypt(ct.first, ct.second, p, x);
    cout << "Decrypted message = " << rm << endl;

    return 0;
}
