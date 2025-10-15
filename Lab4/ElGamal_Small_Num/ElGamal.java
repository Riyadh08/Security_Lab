import java.math.BigInteger;

public class ElGamal {
    // Fast modular exponentiation
    public static BigInteger modExp(BigInteger base, BigInteger exp, BigInteger mod) {
        return base.modPow(exp, mod);
    }

    public static void main(String[] args) {
        BigInteger p = BigInteger.valueOf(23); // prime
        BigInteger g = BigInteger.valueOf(5);  // generator
        BigInteger x = BigInteger.valueOf(6);  // private key
        BigInteger y = g.modPow(x, p);         // public key

        System.out.println("Public key (p,g,y): (" + p + "," + g + "," + y + ")");
        System.out.println("Private key (x): " + x);

        BigInteger m = BigInteger.valueOf(13); // message
        BigInteger k = BigInteger.valueOf(15); // random ephemeral key

        // Encryption
        BigInteger c1 = g.modPow(k, p);
        BigInteger c2 = (m.multiply(y.modPow(k, p))).mod(p);
        System.out.println("Ciphertext: (" + c1 + "," + c2 + ")");

        // Decryption
        BigInteger s = c1.modPow(x, p);
        BigInteger s_inv = s.modInverse(p);
        BigInteger decrypted = (c2.multiply(s_inv)).mod(p);
        System.out.println("Decrypted message: " + decrypted);
    }
}
