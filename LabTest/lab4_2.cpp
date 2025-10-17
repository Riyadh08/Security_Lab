// ElGamal Digital Signature Scheme Implementation

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Compute (base^exp) % mod
ll modExp(ll base, ll exp, ll n) {
    ll result = 1;
    base %= n;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % n;
        exp >>= 1;
        base = (base * base) % n;
    }
    return result;
}

// Compute modular inverse of a mod m
ll modInverse(ll a, ll b) {
    ll x0 =1, x1 = 0;

    while (b != 0){
        ll q = a / b;
        ll rem = a % b;
        a = b;
        b = rem;

        ll temp = x0 - q * x1;
        x0 = x1;
        x1 = temp;  
    }
    if (a != 1) return -1; // Inverse doesn't exist
    if (x0 < 0) x0 += b;  // Make positive  
    return x0;
}

int main() {
    // Small ElGamal parameters (for demo only)
    ll p = 467;      // prime modulus
    ll g = 2;        // generator
    ll a = 127;      // private key
    ll h = modExp(g, a, p); // public key

    cout << "Public key (p, g, h): (" << p << ", " << g << ", " << h << ")\n";
    cout << "Private key a = " << a << "\n";

    // Message
    long long m = 123;
    cout << "Message m = " << m << "\n";

    // Choose random k such that gcd(k, p-1)=1
    ll k = 61;
    ll kInv = modInverse(k, p - 1);

    // Signature generation
    ll y1 = modExp(g, k, p);
    ll y2 = ((m - a * y1) * kInv) % (p - 1);
    if (y2 < 0) y2 += (p - 1);

    cout << "Signature: (y1, y2) = (" << y1 << ", " << y2 << ")\n";

    // Verification
    ll left = (modExp(h, y1, p) * modExp(y1, y2, p)) % p;
    ll right = modExp(g, m, p);

    cout << "Verification: " << left << " vs " << right << "\n";
    if (left == right)
        cout << "Signature is valid!\n";
    else
        cout << " Signature is invalid!\n";

    return 0;
}
