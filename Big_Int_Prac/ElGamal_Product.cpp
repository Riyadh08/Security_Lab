#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
using namespace std;
using namespace boost::multiprecision;

using BigInt = cpp_int;

// Modular inverse using Extended Euclidean Algorithm
BigInt modInverse(BigInt a, BigInt m) {
    BigInt m0 = m, y = 0, x = 1;
    if (m == 1) return 0;

    while (a > 1) {
        BigInt q = a / m;
        BigInt t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// Key generation
pair<BigInt, BigInt> keyGen(BigInt p, BigInt g) {
    boost::random::mt19937 gen((unsigned)time(0));
    boost::random::uniform_int_distribution<long long> dist(2, 1e9);

    BigInt x = dist(gen);        // private key
    BigInt y = powm(g, x, p);    // public key
    return {x, y};
}

// Encrypt single message
pair<BigInt, BigInt> encrypt(BigInt m, BigInt p, BigInt g, BigInt y) {
    boost::random::mt19937 gen((unsigned)time(0));
    boost::random::uniform_int_distribution<long long> dist(2, 1e9);

    BigInt k = dist(gen);
    BigInt c1 = powm(g, k, p);
    BigInt c2 = (m * powm(y, k, p)) % p;
    return {c1, c2};
}

// Decrypt
BigInt decrypt(BigInt c1, BigInt c2, BigInt p, BigInt x) {
    BigInt s = powm(c1, x, p);
    BigInt sInv = modInverse(s, p);
    return (c2 * sInv) % p;
}

// Product encryption: combine ciphertexts
pair<BigInt, BigInt> productEncrypt(BigInt m1, BigInt m2, BigInt p, BigInt g, BigInt y) {
    auto ct1 = encrypt(m1, p, g, y);
    auto ct2 = encrypt(m2, p, g, y);

    BigInt C1 = (ct1.first * ct2.first) % p;
    BigInt C2 = (ct1.second * ct2.second) % p;

    return {C1, C2};
}

// Demo
int main() {
    BigInt p("30803");  // small prime for demo
    BigInt g = 2;

    auto keys = keyGen(p, g);
    BigInt x = keys.first; // private
    BigInt y = keys.second; // public

    cout << "Prime p = " << p << "\n";
    cout << "Generator g = " << g << "\n";
    cout << "Private key x = " << x << "\n";
    cout << "Public key y = " << y << "\n";

    BigInt m1("123");
    BigInt m2("456");

    auto ct = productEncrypt(m1, m2, p, g, y);
    cout << "Ciphertext (Product): C1 = " << ct.first << ", C2 = " << ct.second << "\n";

    BigInt decrypted = decrypt(ct.first, ct.second, p, x);
    cout << "Decrypted product = " << decrypted << "\n";
    cout << "Check m1*m2 mod p = " << (m1 * m2) % p << "\n";

    return 0;
}
