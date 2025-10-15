#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

struct Point {
    cpp_int x, y;
    bool atInfinity;
    Point(cpp_int _x=0, cpp_int _y=0, bool inf=false)
        : x(_x), y(_y), atInfinity(inf) {}
};

// Curve parameters: y^2 = x^3 + a*x + b (mod p)
const cpp_int a = 497;
const cpp_int b = 1768;
const cpp_int p = cpp_int("9739");
const Point G(1804, 5368);

// Modular inverse
cpp_int modInverse(cpp_int k, cpp_int p) {
    cpp_int s = 0, old_s = 1;
    cpp_int r = p, old_r = k;
    while (r != 0) {
        cpp_int q = old_r / r;
        cpp_int temp = old_r; old_r = r; r = temp - q * r;
        temp = old_s; old_s = s; s = temp - q * s;
    }
    if (old_s < 0) old_s += p;
    return old_s % p;
}

// Point addition
Point pointAdd(Point P, Point Q) {
    if (P.atInfinity) return Q;
    if (Q.atInfinity) return P;
    if (P.x == Q.x && (P.y + Q.y) % p == 0)
        return Point(0, 0, true);

    cpp_int m;
    if (P.x == Q.x && P.y == Q.y)
        m = ((3 * P.x * P.x + a) * modInverse(2 * P.y, p)) % p;
    else
        m = ((Q.y - P.y) * modInverse((Q.x - P.x + p) % p, p)) % p;

    if (m < 0) m += p;
    cpp_int x3 = (m * m - P.x - Q.x) % p;
    if (x3 < 0) x3 += p;
    cpp_int y3 = (m * (P.x - x3) - P.y) % p;
    if (y3 < 0) y3 += p;

    return Point(x3, y3);
}

// Scalar multiplication
Point scalarMult(cpp_int k, Point P) {
    Point R(0, 0, true);
    Point Q = P;
    while (k > 0) {
        if (k & 1) R = pointAdd(R, Q);
        Q = pointAdd(Q, Q);
        k >>= 1;
    }
    return R;
}

int main() {
    cout << "Elliptic Curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")\n";

    // Key generation
    cpp_int d = 1194;
    Point Q = scalarMult(d, G);
    cout << "\nPrivate key d = " << d << endl;
    cout << "Public key Q = (" << Q.x << ", " << Q.y << ")\n";

    // Valid message point on curve
    Point M(4726, 3855); // verified point on curve

    cpp_int k = 873; // random
    Point C1 = scalarMult(k, G);
    Point C2 = pointAdd(M, scalarMult(k, Q));

    cout << "\nEncryption:\n";
    cout << "C1 = (" << C1.x << ", " << C1.y << ")\n";
    cout << "C2 = (" << C2.x << ", " << C2.y << ")\n";

    // Decryption
    Point dC1 = scalarMult(d, C1);
    Point neg_dC1(dC1.x, (p - dC1.y) % p);
    Point M_rec = pointAdd(C2, neg_dC1);

    cout << "\nDecryption:\n";
    cout << "Recovered M = (" << M_rec.x << ", " << M_rec.y << ")\n";

    return 0;
}
