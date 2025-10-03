#include <bits/stdc++.h>
using namespace std;
#define ll long long

// ll modExp(ll a, ll b, ll n) {
//     if (b == 0) return 1;
//     ll half = modExp(a, b / 2, n);  // compute once
//     ll result = (half * half) % n;
//     if (b & 1) result = (result * a) % n;
//     return result;
// }

// ll  modExp(ll a, ll b, ll n){
//     if(b==0) return 1;
   
//     if(b&1){
//         return a * (modExp(a, b/2, n) * modExp(a, b/2, n)) % n;
//     }
//     return (modExp(a, b/2, n) * modExp(a, b/2, n)) % n;
// }

ll modExp(ll a, ll b, ll n){

    ll res = 1;
    a = a % n; 
    while(b>0){

        if(b&1) res = (res * a) % n;
        b >>= 1;
        a = (a * a) % n;
    }
    return res;

}
// Modular inverse using Extended Euclidean Algorithm
ll modInverse(ll e, ll phi) {
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

int main() {
    long long p = 23;     // prime
    long long g = 5;      // generator g is a primitive root modulo 𝑝, where p is a prime.
    long long x = 6;      // private key
    long long y = modExp(g, x, p);  // public key y = g^x % p

    cout << "Public key (p,g,y):" << p << "," << g << "," << y << "\n";
    cout << "Private key (x): " << x << "\n";

    long long m = 13;   // message
    long long k = 15;   // random ephemeral key

    // Encryption
    long long c1 = modExp(g, k, p);//c1 = g^k % p
    long long c2 = (m * modExp(y, k, p)) % p;//c2 = m.(y^k % p) % p
    cout << "Ciphertext: (" << c1 << "," << c2 << ")\n";

    // Decryption
    long long s = modExp(c1, x, p);//s = c1^x % p
    long long s_inv = modInverse(s, p);//s^-1 % p
    long long decrypted = (c2 * s_inv) % p;//m = (c2 * s^-1) % p
    cout << "Decrypted message: " << decrypted << "\n";

    return 0;
}

