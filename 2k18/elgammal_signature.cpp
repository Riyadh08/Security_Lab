#include <iostream>
#include <cmath>

// Function to calculate the modular exponentiation (base^exponent mod modulus)
long long modExp(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

// Function to calculate the greatest common divisor (Euclidean algorithm)
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to calculate the modular inverse (using Extended Euclidean algorithm)
long long modInverse(long long a, long long modulus) {
    long long b = modulus;
    long long x = 0, y = 1, lastX = 1, lastY = 0, temp;

    while (b != 0) {
        long long quotient = a / b;
        long long remainder = a % b;

        a = b;
        b = remainder;

        temp = x;
        x = lastX - quotient * x;
        lastX = temp;

        temp = y;
        y = lastY - quotient * y;
        lastY = temp;
    }

    if (lastX < 0)
        lastX += modulus;

    return lastX;
}

// Function to generate ElGamal signature
void generateElGamalSignature(long long message, long long p, long long g, long long x,
                             long long &r, long long &s) {
    long long k;

    do {
        k = rand() % (p - 2) + 1;  // Randomly choose a value for k (1 <= k <= p-2)
    } while (gcd(k, p - 1) != 1);  // Ensure k is coprime with p-1

    r = modExp(g, k, p);  // r = g^k mod p
    long long kInverse = modInverse(k, p - 1);  // Calculate the modular inverse of k

    long long hash = message % (p - 1);  // Calculate the hash of the message

    s = (kInverse * (hash - x * r)) % (p - 1);  // s = (k^(-1) * (hash - x * r)) mod (p-1)
    if (s < 0)
        s += p - 1;
}

// Function to verify ElGamal signature
bool verifyElGamalSignature(long long message, long long p, long long g, long long y,
                            long long r, long long s) {
    long long hash = message % (p - 1);  // Calculate the hash of the message

    long long v1 = modExp(y, r, p);  // v1 = y^r mod p
    long long v2 = modExp(r, s, p);  // v2 = r^s mod p

    long long left = (v1 * v2) % p;  // Calculate the left side of the equation

    long long right = modExp(g, hash, p);  // Calculate the right side of the equation

    return left == right;
}

int main() {
    // Parameters for the ElGamal signature scheme
    long long p = 23;  // Prime number
    long long g = 5;  // Generator
    long long x = 7;  // Secret key
    long long y = modExp(g, x, p);  // Public key

    // Message to be signed
    long long message = 11;

    // Generate the ElGamal signature
    long long r, s;
    generateElGamalSignature(message, p, g, x, r, s);

    // Verify the ElGamal signature
    bool isValid = verifyElGamalSignature(message, p, g, y, r, s);

    if (isValid) {
        std::cout << "Signature is valid." << std::endl;
    } else {
        std::cout << "Signature is not valid." << std::endl;
    }

    return 0;
}
