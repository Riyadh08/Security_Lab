#include <iostream>
#include <cmath>
using namespace std;

// Define a point on the elliptic curve
struct Point {
    long long x, y;
    bool atInfinity;

    Point(long long _x = 0, long long _y = 0, bool inf = false)
        : x(_x), y(_y), atInfinity(inf) {}
};

// Parameters for the curve: y^2 = (x^3 + a*x + b) mod p
const long long a = 2;
const long long b = 3;
const long long p = 97; // small prime

// Base point (generator)
const Point G(3, 6);

// Modular arithmetic
long long modInverse(long long k, long long p) {
    k = (k % p + p) % p;
    for (long long x = 1; x < p; x++)
        if ((k * x) % p == 1)
            return x;
    return -1;
}

// Point addition
Point pointAdd(Point P, Point Q) {
    if (P.atInfinity) return Q;
    if (Q.atInfinity) return P;

    if (P.x == Q.x && (P.y + Q.y) % p == 0)
        return Point(0, 0, true); // Point at infinity

    long long m;
    if (P.x == Q.x && P.y == Q.y)
        m = (3 * P.x * P.x + a) * modInverse(2 * P.y, p) % p;
    else
        m = (Q.y - P.y) * modInverse(Q.x - P.x, p) % p;

    long long x3 = (m * m - P.x - Q.x) % p;
    long long y3 = (m * (P.x - x3) - P.y) % p;
    x3 = (x3 + p) % p;
    y3 = (y3 + p) % p;

    return Point(x3, y3);
}

// Scalar multiplication (k * P)
Point scalarMult(long long k, Point P) {
    Point R(0, 0, true); // Point at infinity
    Point Q = P;
    while (k > 0) {
        if (k & 1)
            R = pointAdd(R, Q);
        Q = pointAdd(Q, Q);
        k >>= 1;
    }
    return R;
}

// Demo: ECC key generation, encryption, decryption
int main() {
    cout << "Elliptic Curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")\n";

    //Key generation
    long long d = 7; // private key (random)
    Point Q = scalarMult(d, G); // public key
    cout << "Private key d = " << d << endl;
    cout << "Public key Q = (" << Q.x << ", " << Q.y << ")\n";

    //Encryption
    cout << "\nEncryption:\n";
    Point M(17, 10); // message point on curve (for demo)
    long long k = 5; // random integer
    Point C1 = scalarMult(k, G);
    Point kQ = scalarMult(k, Q);
    Point C2 = pointAdd(M, kQ);
    cout << "Ciphertext C1 = (" << C1.x << ", " << C1.y << ")\n";
    cout << "Ciphertext C2 = (" << C2.x << ", " << C2.y << ")\n";

    //Decryption
    cout << "\nDecryption:\n";
    Point dC1 = scalarMult(d, C1);
    Point neg_dC1(dC1.x, (-dC1.y + p) % p); // inverse point
    Point M_recovered = pointAdd(C2, neg_dC1);

    cout << "Recovered message M = (" << M_recovered.x << ", " << M_recovered.y << ")\n";

    return 0;
}
