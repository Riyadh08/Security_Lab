#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

#define Point pair<cpp_int, cpp_int>

// Elliptic Curve parameters
cpp_int p = 23;    // prime modulus (you can replace with large prime)
cpp_int a = 1;     // curve coefficient a
cpp_int b = 1;     // curve coefficient b
Point G = {13, 7}; // base point

// Modular exponentiation (base^exp % p)
cpp_int power(cpp_int base, cpp_int exp) {
    cpp_int result = 1;
    base %= p;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % p;
        base = (base * base) % p;
        exp /= 2;
    }
    return result % p;
}

// Modular inverse: a^(-1) mod p  (using Fermat’s Little Theorem)
cpp_int modInverse(cpp_int n) {
    n = (n % p + p) % p;
    return power(n, p - 2);
}

// Point addition on elliptic curve
Point pointAddition(Point P, Point Q) {
    if (P.first == -1 && P.second == -1) return Q;
    if (Q.first == -1 && Q.second == -1) return P;

    cpp_int x1 = P.first, y1 = P.second;
    cpp_int x2 = Q.first, y2 = Q.second;
    cpp_int slope;

    if (x1 == x2 && y1 == y2) {
        // Point doubling: λ = (3*x1^2 + a) / (2*y1)
        cpp_int numerator = (3 * x1 * x1 + a) % p;
        cpp_int denominator = (2 * y1) % p;
        slope = (numerator * modInverse(denominator)) % p;
    } else {
        // Point addition: λ = (y2 - y1) / (x2 - x1)
        cpp_int numerator = (y2 - y1 + p) % p;
        cpp_int denominator = (x2 - x1 + p) % p;
        slope = (numerator * modInverse(denominator)) % p;
    }

    if (slope < 0) slope += p;

    // x3 = λ^2 - x1 - x2
    cpp_int x3 = (slope * slope - x1 - x2) % p;
    if(x3 < 0) x3 += p;

    // y3 = λ*(x1 - x3) - y1
    cpp_int y3 = (slope * (x1 - x3) - y1) % p;
    if(y3 < 0) y3 += p;

    return {x3, y3};
}

// Scalar multiplication using double-and-add algorithm
Point scalarMultiply(cpp_int k, Point P) {
    Point result = {-1, -1};
    Point addend = P;

    while (k > 0) {
        if (k & 1)
            result = pointAddition(result, addend);
        addend = pointAddition(addend, addend);
        k /= 2;
        //k >>= 1;
    }
    return result;
}

// --- Main Demonstration ---
int main() {
    cout << "Curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")\n";
    cout << "Base Point G: (" << G.first << ", " << G.second << ")\n";
    cout << "--------------------------------------------------------\n";

    cpp_int alice_pr_key = 6;
    cout << "Alice's Private Key (secret): " << alice_pr_key << endl;

    Point alice_pb_key = scalarMultiply(alice_pr_key, G);
    cout << "Alice's Public Key (shared): (" << alice_pb_key.first << ", " << alice_pb_key.second << ")\n\n";

    cpp_int bob_pr_key = 11;
    cout << "Bob's Private Key (secret): " << bob_pr_key << endl;

    Point bob_pb_key = scalarMultiply(bob_pr_key, G);
    cout << "Bob's Public Key (shared): (" << bob_pb_key.first << ", " << bob_pb_key.second << ")\n\n";

    cout << "Both parties now compute a shared secret...\n";

    Point alice_shared_secret = scalarMultiply(alice_pr_key, bob_pb_key);
    cout << "Alice's computed shared secret: (" << alice_shared_secret.first << ", " << alice_shared_secret.second << ")\n";

    Point bob_shared_secret = scalarMultiply(bob_pr_key, alice_pb_key);
    cout << "Bob's computed shared secret:   (" << bob_shared_secret.first << ", " << bob_shared_secret.second << ")\n\n";

    if (alice_shared_secret == bob_shared_secret)
        cout << "Success! Both parties have the same shared secret.\n";
    else
        cout << "Error! Shared secrets do not match.\n";

    return 0;
}
