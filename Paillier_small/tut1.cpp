#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Fast modular exponentiation: base^exp % mod
ll modexp(ll base, ll exp, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Extended Euclidean Algorithm (for modular inverse)
ll modInv(ll e, ll phi) {
    ll a = e, b = phi;
    ll x0 = 1, x1 = 0;

    while (b != 0) {
        ll q = a / b;
        ll rem = a % b;       // separate remainder
        a = b;
        b = rem;

        ll temp = x0 - q * x1; // separate temp for coefficient
        x0 = x1;
        x1 = temp;
    }

    if (a != 1) return -1;     // inverse doesn't exist if gcd != 1
    if (x0 < 0) x0 += phi;     // make inverse positive
    return x0;
}

// L function: (u - 1) / n
ll L_function(ll u, ll n) {
    return (u - 1) / n;
}

int main() {
    // -----------------------------
    // Key generation (toy example)
    // -----------------------------
    ll p = 47;
    ll q = 59;
    ll n = p * q;        // 2773
    ll nsq = n * n;      // n^2
    ll g = n + 1;        // common safe choice

    // lambda = lcm(p-1, q-1)
    ll p1 = p - 1, q1 = q - 1;
    ll gcd_pq = gcd(p1, q1);
    ll lambda = (p1 / gcd_pq) * q1;

    // mu = modular inverse of lambda mod n
    ll mu = modInv(lambda, n);

    cout << "Public key (n, g) = (" << n << ", " << g << ")\n";
    cout << "Private key (lambda, mu) = (" << lambda << ", " << mu << ")\n\n";

    // -----------------------------
    // Encrypt a message
    // -----------------------------
    ll m = 123;   // message, must be < n
    ll r = 456;   // random r coprime with n
    if (gcd(r, n) != 1) {
        cout << "r not coprime with n, pick another.\n";
        return 1;
    }

    ll gm = modexp(g, m, nsq);
    ll rn = modexp(r, n, nsq);
    ll c = (gm * rn) % nsq;

    cout << "Message m = " << m << "\n";
    cout << "Ciphertext c = " << c << "\n\n";

    // -----------------------------
    // Decrypt
    // -----------------------------
    ll u = modexp(c, lambda, nsq);
    ll L = L_function(u, n);
    ll m_rec = (L * mu) % n;

    cout << "Decrypted message = " << m_rec << "\n\n";

    // -----------------------------
    // Homomorphic property demo
    // -----------------------------
    cout<<"Homo morphic property: "<<endl;
    ll m1 = 50, m2 = 73;
    ll r1 = 23, r2 = 77;
    ll c1 = (modexp(g, m1, nsq) * modexp(r1, n, nsq)) % nsq;
    ll c2 = (modexp(g, m2, nsq) * modexp(r2, n, nsq)) % nsq;

    ll cprod = (c1 * c2) % nsq;  // Enc(m1) * Enc(m2) = Enc(m1+m2)

    ll u2 = modexp(cprod, lambda, nsq);
    ll L2 = L_function(u2, n);
    ll m_sum = (L2 * mu) % n;

    cout << "m1 = " << m1 << ", m2 = " << m2 << "\n";
    cout << "Decrypted sum (homomorphic) = " << m_sum << "\n";

    return 0;
}
