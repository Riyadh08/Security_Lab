package ryad.elgamal;

import java.math.BigInteger;
import java.security.SecureRandom;

public class ElGamalProductCipher {

    private static final SecureRandom rnd = new SecureRandom();

    // Key generation: returns {x, h} where x is private, h is public
    public static BigInteger[] keyGen(BigInteger p, BigInteger g) {
        BigInteger x;
        do {
            x = new BigInteger(p.bitLength() - 1, rnd);
        } while (x.compareTo(BigInteger.TWO) < 0 || x.compareTo(p.subtract(BigInteger.TWO)) > 0);

        BigInteger h = g.modPow(x, p); // public key
        return new BigInteger[]{x, h};
    }

    // Encrypt single message (standard ElGamal)
    public static BigInteger[] encrypt(BigInteger m, BigInteger p, BigInteger g, BigInteger h) {
        BigInteger r;
        do {
            r = new BigInteger(p.bitLength() - 1, rnd);
        } while (r.compareTo(BigInteger.TWO) < 0 || r.compareTo(p.subtract(BigInteger.TWO)) > 0);

        BigInteger c1 = g.modPow(r, p);
        BigInteger c2 = m.multiply(h.modPow(r, p)).mod(p);
        return new BigInteger[]{c1, c2};
    }

    // Decrypt (standard ElGamal)
    public static BigInteger decrypt(BigInteger c1, BigInteger c2, BigInteger p, BigInteger x) {
        BigInteger s = c1.modPow(x, p);
        BigInteger sInv = s.modInverse(p);
        return c2.multiply(sInv).mod(p);
    }

    // Encrypt two messages as a "product cipher"
    public static BigInteger[] productEncrypt(BigInteger m1, BigInteger m2, BigInteger p, BigInteger g, BigInteger h) {
        // Encrypt message 1
        BigInteger[] ct1 = encrypt(m1, p, g, h);
        BigInteger c11 = ct1[0];
        BigInteger c21 = ct1[1];

        // Encrypt message 2
        BigInteger[] ct2 = encrypt(m2, p, g, h);
        BigInteger c12 = ct2[0];
        BigInteger c22 = ct2[1];

        // Multiply ciphertext components
        BigInteger C1 = c11.multiply(c12).mod(p);
        BigInteger C2 = c21.multiply(c22).mod(p);

        return new BigInteger[]{C1, C2};
    }

    // Demo
    public static void main(String[] args) {
        // Example small prime (for demo only!)
        BigInteger p = new BigInteger("30803"); // prime
        BigInteger g = new BigInteger("2");     // generator

        // Key generation
        BigInteger[] keys = keyGen(p, g);
        BigInteger x = keys[0]; // private key
        BigInteger h = keys[1]; // public key

        System.out.println("Prime p = " + p);
        System.out.println("Generator g = " + g);
        System.out.println("Private key x = " + x);
        System.out.println("Public key h = " + h);

        // Messages
        BigInteger m1 = new BigInteger("123");
        BigInteger m2 = new BigInteger("456");
        System.out.println("Message 1 = " + m1);
        System.out.println("Message 2 = " + m2);

        // Product encryption
        BigInteger[] ct = productEncrypt(m1, m2, p, g, h);
        BigInteger C1 = ct[0];
        BigInteger C2 = ct[1];
        System.out.println("Ciphertext (Product): C1 = " + C1 + ", C2 = " + C2);

        // Decryption gives m1 * m2 mod p
        BigInteger decrypted = decrypt(C1, C2, p, x);
        System.out.println("Decrypted product = " + decrypted);

        System.out.println("Check: m1*m2 mod p = " + m1.multiply(m2).mod(p));
    }
}
