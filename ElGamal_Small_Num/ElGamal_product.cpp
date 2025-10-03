#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Fast modular exponentiation
ll modExp(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while(exp) {
        if(exp & 1) res = (res * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return res;
}

// Modular inverse using Fermat's little theorem (works because p is prime)
ll modInverse(ll a, ll p) {
    return modExp(a, p - 2, p);
}

int main() {
    ll p = 23;  // prime modulus
    ll g = 5;   // generator
    ll a = 6;   // private key
    ll y = modExp(g, a, p); // public key

    cout << "Public keys (p,g,y): " << p << " " << g << " " << y << endl;
    cout << "Private key (a): " << a << endl;

    // Messages
    ll m1 = 4;
    ll m2 = 3;

    // Random secret keys
    ll r1 = 7;
    ll r2 = 11;

    // Individual encryptions
    ll C11 = modExp(g, r1, p);
    ll C21 = (m1 * modExp(y, r1, p)) % p;

    ll C12 = modExp(g, r2, p);
    ll C22 = (m2 * modExp(y, r2, p)) % p;

    cout << "Individual ciphertexts:" << endl;
    cout << "C1: (" << C11 << "," << C21 << ")  C2: (" << C12 << "," << C22 << ")" << endl;

    // Combined ciphertext (product cipher)
    ll C1 = (C11 * C12) % p;
    ll C2 = (C21 * C22) % p;

    cout << "Combined ciphertext: (" << C1 << "," << C2 << ")" << endl;

    // Decryption of combined ciphertext
    ll s = modExp(C1, a, p);
    ll s_inv = modInverse(s, p);
    ll decrypted_product = (C2 * s_inv) % p;

    cout << "Decrypted product of messages: " << decrypted_product << endl;

    return 0;
}
