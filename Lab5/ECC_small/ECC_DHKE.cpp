#include <bits/stdc++.h>
using namespace std;
#define ll long long
// A small prime number for our finite field
const int p = 23;
// 'a' coefficient of the curve equation
const int a = 1;
// 'b' coefficient of the curve equation
const int b = 1;

// The base point (or generator point) G on the curve
const pair<int, int> G = {13, 7};

// Function to compute (base^exp) % mod using modular exponentiation
long long power(long long base, long long exp) {
    long long res = 1;
    base %= p;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % p;
        base = (base * base) % p;
        exp /= 2;
    }
    return res;
}

// Function to compute the modular inverse of n modulo p
// This is used for division in the finite field: (a / b) mod p = (a * b^-1) mod p
int modInverse(int n) {
    return power(n, p - 2);
}

// --- Core ECC Operations ---

// Point Addition: Computes R = P + Q
pair<int, int> pointAddition(const pair<int, int>& P, const pair<int, int>& Q) {
    // The point at infinity (identity element), represented here as {-1, -1}
    if (P.first == -1 && P.second == -1) return Q;
    if (Q.first == -1 && Q.second == -1) return P;

    int x1 = P.first;
    int y1 = P.second;
    int x2 = Q.first;
    int y2 = Q.second;

    int solpe;

    if (x1 == x2 && y1 == y2) { // Case 1: Point Doubling (P == Q)
        // solpe = (3*x1^2 + a) * (2*y1)^-1 mod p
        int numerator = (3 * x1 * x1 + a) % p;
        int denominator = (2 * y1) % p;
        solpe = (numerator * modInverse(denominator)) % p;
    } else { // Case 2: Point Addition (P != Q)
        // solpe = (y2 - y1) * (x2 - x1)^-1 mod p
        int numerator = (y2 - y1);
        int denominator = (x2 - x1);
        solpe = (numerator * modInverse(denominator)) % p;
    }
    
    if (solpe < 0) solpe += p;

    // Calculate the coordinates of the new point R(x3, y3)
    // x3 = (solpe^2 - x1 - x2) mod p
    int x3 = (solpe * solpe - x1 - x2) % p;
    if (x3 < 0) x3 += p;

    // y3 = (solpe * (x1 - x3) - y1) mod p
    int y3 = (solpe * (x1 - x3) - y1) % p;
    if (y3 < 0) y3 += p;

    return {x3, y3};
}

// Scalar Multiplication: Computes R = k * P
// This is done using the "double-and-add" algorithm.
pair<int, int> scalarMultiply(int k, const pair<int, int>& P) {
    pair<int, int> result = {-1, -1}; // Start with the point at infinity
    pair<int, int> addend = P;

    while (k > 0) {
        if (k & 1) { // If the last bit of k is 1
            result = pointAddition(result, addend);
        }
        addend = pointAddition(addend, addend); // Double the point
        k >>= 1; // Move to the next bit of k
    }
    return result;
}

int main() {
    cout << "--- Simplified ECC Demonstration (Educational Use Only) ---" << endl;
    cout << "Curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")" << endl;
    cout << "Base Point G: (" << G.first << ", " << G.second << ")" << endl;
    cout << "--------------------------------------------------------" << endl;
    
    // --- Key Generation ---
    // Alice chooses a secret private key (a random integer)
    int alice_private_key = 6;
    cout << "Alice's Private Key (secret): " << alice_private_key << endl;

    // Alice computes her public key: P_A = private_key_A * G
    pair<int, int> alice_public_key = scalarMultiply(alice_private_key, G);
    cout << "Alice's Public Key (shared): (" << alice_public_key.first << ", " << alice_public_key.second << ")" << endl << endl;

    // Bob chooses his secret private key
    int bob_private_key = 11;
    cout << "Bob's Private Key (secret): " << bob_private_key << endl;

    // Bob computes his public key: P_B = private_key_B * G
    pair<int, int> bob_public_key = scalarMultiply(bob_private_key, G);
    cout << "Bob's Public Key (shared): (" << bob_public_key.first << ", " << bob_public_key.second << ")" << endl;
    cout << "--------------------------------------------------------" << endl;

    // --- Shared Secret Generation (ECDH) ---
    cout << "Both parties will now compute a shared secret without" << endl;
    cout << "exchanging their private keys." << endl << endl;

    // Alice computes the shared secret using her private key and Bob's public key
    // Secret_A = private_key_A * P_B
    pair<int, int> alice_shared_secret = scalarMultiply(alice_private_key, bob_public_key);
    cout << "Alice's computed shared secret: (" << alice_shared_secret.first << ", " << alice_shared_secret.second << ")" << endl;

    // Bob computes the shared secret using his private key and Alice's public key
    // Secret_B = private_key_B * P_A
    pair<int, int> bob_shared_secret = scalarMultiply(bob_private_key, alice_public_key);
    cout << "Bob's computed shared secret:   (" << bob_shared_secret.first << ", " << bob_shared_secret.second << ")" << endl << endl;

    // The shared secrets must be identical
    if (alice_shared_secret.first == bob_shared_secret.first && 
        alice_shared_secret.second == bob_shared_secret.second) {
        cout << "Success! Both parties have computed the same shared secret." << endl;
    } else {
        cout << "Error! Shared secrets do not match." << endl;
    }
    
    return 0;
}