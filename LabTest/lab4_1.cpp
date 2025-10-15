//ElGamal product Cipher

#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Given modular exponentiation function
ll modExp(ll a, ll b, ll n){
    ll res = 1;
    a = a % n;
    while (b > 0) {
        if (b & 1) res = (res * a) % n;
        a = (a * a) % n;
        b >>= 1;
    }
    return res;
}

// Given modular inverse function
ll modInverse(ll e, ll phi) {
    ll a = e, b = phi;
    ll x0 = 1, x1 = 0;

    while (b != 0) {
        ll q = a / b;
        ll rem = a % b;
        a = b;
        b = rem;

        ll temp = x0 - q * x1;
        x0 = x1;
        x1 = temp;
    }

    if (a != 1) return -1; // Inverse doesn’t exist
    if (x0 < 0) x0 += phi;
    return x0;
}

int main() {
    // === Step 1: Teacher-provided parameters ===
    ll p = 467;   // large prime
    ll g = 2;     // primitive root modulo p
    ll a = 127;   // private key (provided)
    ll m = 123;   // message (provided)
    ll k = 53;    // random nonce chosen by teacher (gcd(k, p-1)=1)

    cout << "Given parameters:\n";
    cout << "Prime (p): " << p << "\n";
    cout << "Generator (g): " << g << "\n";
    cout << "Private key (a): " << a << "\n";
    cout << "Message (m): " << m << "\n";
    cout << "Random k: " << k << "\n\n";

    // === Step 2: Compute public key ===
    ll h = modExp(g, a, p);   // h = g^a mod p
    cout << "Public key (h = g^a mod p): " << h << "\n\n";

    // === Step 3: Signature generation ===
    ll y1 = modExp(g, k, p);              // y1 = g^k mod p
    ll k_inv = modInverse(k, p - 1);      // modular inverse of k mod (p-1)

    if (k_inv == -1) {
        cout << "Inverse of k does not exist. Choose different k.\n";
        return 0;
    }

    ll y2 = ((m - a * y1) * k_inv) % (p - 1);
    if (y2 < 0) y2 += (p - 1);            // make it positive

    cout << "Signature generation:\n";
    cout << "y1 = g^k mod p = " << y1 << "\n";
    cout << "y2 = (m - a*y1) * k^(-1) mod (p-1) = " << y2 << "\n\n";
    cout << "Signature = (" << y1 << ", " << y2 << ")\n\n";

    // === Step 4: Verification ===
    ll left = (modExp(y1, y2, p) * modExp(h, y1, p)) % p;
    ll right = modExp(g, m, p);

    cout << "Verification:\n";
    cout << "Left side  = (y1^y2 * h^y1) mod p = " << left << "\n";
    cout << "Right side = g^m mod p = " << right << "\n";

    if (left == right)
        cout << "Signature is VALID.\n";
    else
        cout << "Signature is INVALID.\n";

    return 0;
}
