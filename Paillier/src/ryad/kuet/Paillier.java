package ryad.kuet;

import java.math.BigInteger;

public class Paillier {

    // Extended Euclidean Algorithm (for gcd and coefficients)
    private static BigInteger x;
    private static BigInteger y;

    private static BigInteger gcdExtended(BigInteger a, BigInteger b) {
        if (a.equals(BigInteger.ZERO)) {
            x = BigInteger.ZERO;
            y = BigInteger.ONE;
            return b;
        }

        BigInteger gcd = gcdExtended(b.mod(a), a);
        BigInteger x1 = x;
        BigInteger y1 = y;

        // update x, y
        x = y1.subtract((b.divide(a)).multiply(x1));
        y = x1;

        return gcd;
    }

    // Modular inverse using Extended Euclidean Algorithm
    private static BigInteger modInverse(BigInteger A, BigInteger M) {
        BigInteger g = gcdExtended(A, M);
        if (!g.equals(BigInteger.ONE)) {
            throw new ArithmeticException("Inverse doesn't exist");
        }
        return (x.mod(M).add(M)).mod(M);
    }

    // L function for Paillier decryption
    private static BigInteger L(BigInteger x, BigInteger n) {
        return x.subtract(BigInteger.ONE).divide(n);
    }

    // Encryption: c = g^m * r^n mod n^2
    private static BigInteger encryption(BigInteger g, BigInteger m, BigInteger n) {
        BigInteger r = new BigInteger("11"); // random co-prime with n
        if (!gcdExtended(n, r).equals(BigInteger.ONE)) {
            throw new IllegalArgumentException("Random r not coprime with n");
        }

        BigInteger n2 = n.multiply(n);
        BigInteger k1 = g.modPow(m, n2);
        BigInteger k2 = r.modPow(n, n2);
        return k1.multiply(k2).mod(n2);
    }

    // Decryption: m = L(c^λ mod n^2) * μ mod n
    private static BigInteger decryption(BigInteger c, BigInteger lambda, BigInteger n, BigInteger mu) {
        BigInteger n2 = n.multiply(n);
        BigInteger t1 = c.modPow(lambda, n2);
        t1 = L(t1, n);
        return t1.multiply(mu).mod(n);
    }

    // Demo
    public static void main(String[] args) {
        BigInteger p = new BigInteger("10007");
        BigInteger q = new BigInteger("10069");

        BigInteger n = p.multiply(q);
        BigInteger phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));

        if (!gcdExtended(n, phi).equals(BigInteger.ONE)) {
            System.out.println("Wrong Prime");
            return;
        }

        // λ = lcm(p-1, q-1)
        BigInteger lambda = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE))
                .divide(gcdExtended(p.subtract(BigInteger.ONE), q.subtract(BigInteger.ONE)));

        BigInteger g = new BigInteger("13");
        if (!gcdExtended(n, g).equals(BigInteger.ONE)) {
            System.out.println("Wrong G");
            return;
        }

        BigInteger n2 = n.multiply(n);
        BigInteger t1 = g.modPow(lambda, n2);
        t1 = L(t1, n);
        BigInteger mu = modInverse(t1, n);

        // Message
        BigInteger message = new BigInteger("118");
        BigInteger cipher = encryption(g, message, n);

        System.out.println("Cipher text: " + cipher);

        BigInteger rm = decryption(cipher, lambda, n, mu);
        System.out.println("Decrypted message: " + rm);
    }
}
