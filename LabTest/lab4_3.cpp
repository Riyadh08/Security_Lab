#include<bits/stdc++.h>
using namespace std;
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
//using BigInt = cpp_int;

cpp_int modExp(cpp_int base, cpp_int exp, cpp_int p)
{
    cpp_int res = 1;

    while(exp > 0)
    {
        if(exp & 1) res = (res * base) % p;
        base = (base * base) % p;
        exp = exp / 2;
    }
    return res;
}

// Modular inverse using Fermat's Little Theorem (since p is prime)
cpp_int modInv(cpp_int x, cpp_int p)
{
    return modExp(x, p - 2, p);
}


int main()
{
    cpp_int p("999999999999999999999999999999999841");
    cpp_int g = 2;
    cpp_int a = 127;

    cpp_int h = modExp(g, a, p);

    cpp_int ms1 = 123;
    cpp_int ms2 = 77;

    cpp_int k1 = 53;
    cpp_int k2 = 97;

    cout << "Parameters: p=" << p << " g=" << g << " a(private)=" << a << " h(public)=" << h << "\n\n";
    cout << "Messages: ms1=" << ms1 << ", ms2=" << ms2 << "\n\n";

    cpp_int c11 = modExp(g, k1, p);
    cpp_int c21 = (ms1 * modExp(h, k1, p)) % p;
    cpp_int c12 = modExp(g, k2, p);
    cpp_int c22 = (ms2 * modExp(h, k2, p)) % p;

    cpp_int c1 = (c11 * c12) % p;
    cpp_int c2 = (c21 * c22) % p;
    cout << "Product ciphertext: (c1, c2) = (" << c1 << ", " << c2 << ")\n\n";

    cpp_int s = modExp(c1, a, p);
    cpp_int s_inv = modInv(s, p);
    cpp_int dec = (c2 * s_inv) % p;
    cout<<"dec product message: "<<dec<<endl;

    cpp_int exp = (ms1 * ms2) % p;
    cout<<"Expected (ms1 * ms2) mod p : "<<exp<<endl;
    if (dec == exp)
        cout << "Product decryption successful! The ElGamal product cipher works.\n";
    else
        cout << "Mismatch! Something went wrong.\n";


    return 0;
}
