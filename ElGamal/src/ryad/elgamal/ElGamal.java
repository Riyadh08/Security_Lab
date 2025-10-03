package ryad.elgamal;

import java.math.BigInteger;
import java.security.SecureRandom;

public class ElGamal {

    private static final SecureRandom rnd = new SecureRandom();

    // Key Generation: returns {x, y} where x = private key, y = public key
    public static BigInteger[] keyGen(BigInteger p, BigInteger g) {
        BigInteger x; // private key
        do {
            x = new BigInteger(p.bitLength() - 1, rnd);
        } while (x.compareTo(BigInteger.TWO) < 0 || x.compareTo(p.subtract(BigInteger.TWO)) > 0);

        BigInteger y = g.modPow(x, p); // public key
        return new BigInteger[]{x, y};
    }

    // Encryption: returns {c1, c2}
    public static BigInteger[] encrypt(BigInteger m, BigInteger p, BigInteger g, BigInteger y) {
        BigInteger k;
        do {
            k = new BigInteger(p.bitLength() - 1, rnd);
        } while (k.compareTo(BigInteger.TWO) < 0 || k.compareTo(p.subtract(BigInteger.TWO)) > 0);

        BigInteger c1 = g.modPow(k, p);
        BigInteger c2 = m.multiply(y.modPow(k, p)).mod(p);
        return new BigInteger[]{c1, c2};
    }

    // Decryption
    public static BigInteger decrypt(BigInteger c1, BigInteger c2, BigInteger p, BigInteger x) {
        BigInteger s = c1.modPow(x, p);
        BigInteger sInv = s.modInverse(p);
        return c2.multiply(sInv).mod(p);
    }

    // Demo
    public static void main(String[] args) {
        // Example prime (for demo; in practice use a very large prime)
        BigInteger p = new BigInteger("30803"); // must be prime
        BigInteger g = new BigInteger("2");     // generator

        System.out.println("Prime p = " + p);
        System.out.println("Generator g = " + g);

        // Key generation
        BigInteger[] keys = keyGen(p, g);
        BigInteger x = keys[0]; // private key
        BigInteger y = keys[1]; // public key

        System.out.println("Private key x = " + x);
        System.out.println("Public key y = " + y);

        // Message
        BigInteger m = new BigInteger("12345");
        System.out.println("Original message m = " + m);

        // Encrypt
        BigInteger[] ct = encrypt(m, p, g, y);
        System.out.println("Ciphertext: c1 = " + ct[0] + ", c2 = " + ct[1]);

        // Decrypt
        BigInteger rm = decrypt(ct[0], ct[1], p, x);
        System.out.println("Decrypted message = " + rm);
    }
}
