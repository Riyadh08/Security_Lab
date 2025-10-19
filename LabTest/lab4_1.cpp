// ElGamal_product_cipher_demo.cpp

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// fast modular exponentiation
ll modExp(ll a, ll b, ll mod) {
    ll res = 1 % mod;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}

// modular inverse using Fermat (works when mod is prime)
ll modInvPrime(ll x, ll mod) {
    // inverse = x^(mod-2) mod mod
    return modExp((x % mod + mod) % mod, mod - 2, mod);
}

// ElGamal encryption: returns (c1, c2)
pair<ll,ll> elgamal_encrypt(ll m, ll p, ll g, ll h, ll k) {
    ll c1 = modExp(g, k, p);            // g^k mod p
    ll s  = modExp(h, k, p);            // h^k mod p
    ll c2 = (__int128)m * s % p;        // m * s mod p
    return {c1, c2};
}

// ElGamal decryption given (c1,c2) and private key a
ll elgamal_decrypt(pair<ll,ll> cipher, ll p, ll a) {
    ll c1 = cipher.first;
    ll c2 = cipher.second;
    ll s = modExp(c1, a, p);            // c1^a = g^{k*a} = h^k
    ll s_inv = modInvPrime(s, p);
    ll m = (__int128)c2 * s_inv % p;
    if (m < 0) m += p;
    return m;
}

int main() {
    // Example parameters (teacher or chosen)
    ll p = 467;          // prime
    ll g = 2;            // generator
    ll a = 127;          // private key
    ll h = modExp(g, a, p); // public key h = g^a mod p

    // two messages to encrypt (must be in [0, p-1])
    ll m1 = 123;
    ll m2 = 77;

    // random nonces (should be random and invertible mod p-1 in practice,
    // but for encryption only requirement is 1 <= k <= p-2)
    ll k1 = 53;
    ll k2 = 97;

    cout << "Parameters: p=" << p << " g=" << g << " a(private)=" << a << " h(public)=" << h << "\n\n";
    cout << "Messages: m1=" << m1 << ", m2=" << m2 << "\n\n";

    // encrypt messages
    auto c1 = elgamal_encrypt(m1, p, g, h, k1);
    auto c2 = elgamal_encrypt(m2, p, g, h, k2);

    cout << "Ciphertext1: (c1=" << c1.first << ", c2=" << c1.second << ")\n";
    cout << "Ciphertext2: (c1=" << c2.first << ", c2=" << c2.second << ")\n\n";

    // decrypt individually (sanity check)
    ll dec1 = elgamal_decrypt(c1, p, a);
    ll dec2 = elgamal_decrypt(c2, p, a);
    cout << "Decrypted m1 = " << dec1 << "\n";
    cout << "Decrypted m2 = " << dec2 << "\n\n";

    // === Homomorphic / product property demonstration ===
    // Multiply ciphertext components modulo p:
    // (c1_prod, c2_prod) = (c1_1 * c1_2 mod p, c2_1 * c2_2 mod p)
    // This is a valid ElGamal ciphertext for (m1 * m2 mod p) with randomness k1+k2.
    ll c1_prod = (__int128)c1.first * c2.first % p;
    ll c2_prod = (__int128)c1.second * c2.second % p;

    cout << "Product ciphertext: (c1_prod=" << c1_prod << ", c2_prod=" << c2_prod << ")\n";

    // decrypt product ciphertext
    pair<ll,ll> prod_cipher = {c1_prod, c2_prod};
    ll dec_prod = elgamal_decrypt(prod_cipher, p, a);
    cout << "Decrypted product (m1*m2 mod p) = " << dec_prod << "\n";

    // explicit product mod p for verification
    ll expected_prod = (__int128)m1 * m2 % p;
    cout << "Expected (m1*m2 mod p) = " << expected_prod << "\n";

    if (dec_prod == expected_prod) cout << "Product decryption matches expected product. ✅\n";
    else cout << "Mismatch! ❌\n";

    return 0;
}
