//ElGamal Encryption Rerandomization and Homomorphic Multiplication Demo
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// modular exponentiation
ll modExp(ll base, ll exp, ll p)
{
    ll res = 1;
    base %= p;
    while (exp > 0)
    {
        if (exp & 1)
            res = (res * base) % p;
        base = (base * base) % p;
        exp = exp / 2;
    }
    return res;
}

// modular inverse using Fermat’s theorem
ll modInv(ll x, ll p)
{
    return modExp(x, p - 2, p);
}

// === Rerandomization function ===
// Given ciphertext (c1, c2), returns a rerandomized version (c1', c2')
pair<ll, ll> rerandomize(ll c1, ll c2, ll g, ll h, ll p, ll r)
{
    ll c1_new = (c1 * modExp(g, r, p)) % p;
    ll c2_new = (c2 * modExp(h, r, p)) % p;
    return {c1_new, c2_new};
}

int main()
{
    ll p = 10007; // a small prime for demonstration
    ll g = 2;
    ll a = 127;
    ll h = modExp(g, a, p);

    ll ms1 = 123;
    ll ms2 = 77;
    ll k1 = 53;
    ll k2 = 97;

    cout << "Parameters: p=" << p << " g=" << g << " a(private)=" << a << " h(public)=" << h << "\n\n";
    cout << "Messages: ms1=" << ms1 << ", ms2=" << ms2 << "\n\n";

    // Encrypt two messages
    ll c11 = modExp(g, k1, p);
    ll c21 = (ms1 * modExp(h, k1, p)) % p;
    ll c12 = modExp(g, k2, p);
    ll c22 = (ms2 * modExp(h, k2, p)) % p;

    // Product ciphertext (homomorphic property)
    ll c1 = (c11 * c12) % p;
    ll c2 = (c21 * c22) % p;
    cout << "Product ciphertext: (c1, c2) = (" << c1 << ", " << c2 << ")\n\n";

    // Decrypt product
    ll s = modExp(c1, a, p);
    ll s_inv = modInv(s, p);
    ll dec = (c2 * s_inv) % p;

    ll expected = (ms1 * ms2) % p;
    cout << "Decrypted product message: " << dec << endl;
    cout << "Expected (ms1 * ms2 mod p): " << expected << endl;
    cout << ((dec == expected) ? "Product decryption successful!\n" : "Mismatch!\n");

    // === Demonstrate re-randomization ===
    ll r = 111; // new random number
    auto [c1_new, c2_new] = rerandomize(c1, c2, g, h, p, r);

    cout << "\nRerandomized ciphertext: \n";
    cout << "c1' = " << c1_new << "\n";
    cout << "c2' = " << c2_new << "\n";

    // Decrypt rerandomized ciphertext
    ll s2 = modExp(c1_new, a, p);
    ll s2_inv = modInv(s2, p);
    ll dec2 = (c2_new * s2_inv) % p;

    cout << "Decrypted rerandomized message: " << dec2 << "\n";
    cout << ((dec2 == expected) ? "Rerandomization successful (message unchanged).\n"
                                : "Something went wrong in rerandomization!\n");

    return 0;
}
