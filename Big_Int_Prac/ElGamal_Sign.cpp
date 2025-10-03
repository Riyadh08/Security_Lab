#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
using namespace std;
using namespace boost::multiprecision;

using BigInt = cpp_int;

// Modular inverse
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
// Returns (private a, public h)
pair<BigInt, BigInt> keyGen(BigInt p, BigInt g) {
    boost::random::mt19937 gen((unsigned)time(0));
    boost::random::uniform_int_distribution<long long> dist(2, 1e9);

    BigInt a = dist(gen);        // private key
    BigInt h = powm(g, a, p);    // public key
    return {a, h};
}

// Sign message m
pair<BigInt, BigInt> sign(BigInt m, BigInt p, BigInt g, BigInt a) {
    boost::random::mt19937 gen((unsigned)time(0));
    boost::random::uniform_int_distribution<long long> dist(2, 1e9);

    BigInt k;
    do {
        k = dist(gen);
    } while (boost::multiprecision::gcd(k, p - 1) != 1); // gcd(k, p-1)=1

    BigInt y1 = powm(g, k, p);
    BigInt kInv = modInverse(k, p - 1);
    BigInt y2 = (m - a * y1) * kInv % (p - 1);
    if (y2 < 0) y2 += (p - 1);

    return {y1, y2};
}

// Verify signature
bool verify(BigInt m, BigInt y1, BigInt y2, BigInt p, BigInt g, BigInt h) {
    BigInt left = (powm(y1, y2, p) * powm(h, y1, p)) % p;
    BigInt right = powm(g, m, p);
    return left == right;
}

// Demo
int main() {
    BigInt p("30803"); // small prime for demo
    BigInt g = 2;

    auto keys = keyGen(p, g);
    BigInt a = keys.first; // private
    BigInt h = keys.second; // public

    cout << "Prime p = " << p << "\n";
    cout << "Generator g = " << g << "\n";
    cout << "Private key a = " << a << "\n";
    cout << "Public key h = " << h << "\n";

    BigInt m("12345");
    cout << "Message m = " << m << "\n";

    auto sig = sign(m, p, g, a);
    cout << "Signature: y1 = " << sig.first << ", y2 = " << sig.second << "\n";

    bool valid = verify(m, sig.first, sig.second, p, g, h);
    cout << "Signature valid? " << (valid ? "YES" : "NO") << "\n";

    return 0;
}
