#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
using namespace std;
using namespace boost::multiprecision;

// Alias for big integer
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

// Trial division prime factorization (unique factors)
vector<BigInt> primeFactors(BigInt n) {
    vector<BigInt> factors;
    BigInt two = 2;
    while (n % two == 0) {
        factors.push_back(two);
        n /= two;
    }
    for (BigInt i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n);

    // remove duplicates
    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());
    return factors;
}

// Find primitive root modulo p
BigInt findGenerator(BigInt p) {
    BigInt phi = p - 1;
    auto factors = primeFactors(phi);

    for (BigInt g = 2; g < p; g++) {
        bool ok = true;
        for (auto q : factors) {
            if (powm(g, phi / q, p) == 1) { // g^(phi/q) mod p == 1 ?
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    throw runtime_error("No generator found");
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
