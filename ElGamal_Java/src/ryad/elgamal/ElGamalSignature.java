package ryad.elgamal;

import java.math.BigInteger;
import java.security.SecureRandom;

public class ElGamalSignature {

    private static final SecureRandom rnd = new SecureRandom();

    // Extended Euclidean Algorithm for modular inverse
    public static BigInteger modInverse(BigInteger a, BigInteger m) {
        return a.modInverse(m);
    }

    // Key Generation: returns {p, g, x, h}
    // x = private key, h = g^x mod p
    public static BigInteger[] keyGen(BigInteger p, BigInteger g) {
        BigInteger x; // private key
        do {
            x = new BigInteger(p.bitLength() - 1, rnd);
        } while (x.compareTo(BigInteger.TWO) < 0 || x.compareTo(p.subtract(BigInteger.TWO)) > 0);

        BigInteger h = g.modPow(x, p); // public key
        return new BigInteger[]{p, g, x, h};
    }

    // Signature generation: returns (y1, y2)
    // y1 = g^k mod p
    // y2 = (m - a*y1) * k^-1 mod (p-1)
    public static BigInteger[] sign(BigInteger m, BigInteger p, BigInteger g, BigInteger a) {
        BigInteger k;
        do {
            k = new BigInteger(p.bitLength() - 1, rnd);
        } while (!k.gcd(p.subtract(BigInteger.ONE)).equals(BigInteger.ONE)); // k must be coprime to p-1

        BigInteger y1 = g.modPow(k, p);
        BigInteger kInv = modInverse(k, p.subtract(BigInteger.ONE));
        BigInteger y2 = (m.subtract(a.multiply(y1))).multiply(kInv).mod(p.subtract(BigInteger.ONE));

        return new BigInteger[]{y1, y2};
    }

    // Signature verification
    // Verify if: y1^y2 * h^y1 ≡ g^m (mod p)
    public static boolean verify(BigInteger m, BigInteger y1, BigInteger y2, BigInteger p, BigInteger g, BigInteger h) {
        BigInteger left = (y1.modPow(y2, p).multiply(h.modPow(y1, p))).mod(p);
        BigInteger right = g.modPow(m, p);
        return left.equals(right);
    }

    // Demo
    public static void main(String[] args) {
        // Example small prime (for demo only!)
        BigInteger p = new BigInteger("30803"); // must be prime
        BigInteger g = new BigInteger("2");     // primitive root modulo p

        // Key generation
        BigInteger[] keys = keyGen(p, g);
        BigInteger a = keys[2]; // private key
        BigInteger h = keys[3]; // public key

        System.out.println("Prime p = " + p);
        System.out.println("Generator g = " + g);
        System.out.println("Private key a = " + a);
        System.out.println("Public key h = " + h);

        // Message to sign
        BigInteger m = new BigInteger("12345");
        System.out.println("Message m = " + m);

        // Sign
        BigInteger[] sig = sign(m, p, g, a);
        BigInteger y1 = sig[0];
        BigInteger y2 = sig[1];
        System.out.println("Signature: y1 = " + y1 + ", y2 = " + y2);

        // Verify
        boolean valid = verify(m, y1, y2, p, g, h);
        System.out.println("Signature valid? " + valid);
    }
}
