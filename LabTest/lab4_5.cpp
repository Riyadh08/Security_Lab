#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

cpp_int modExp1(cpp_int base, cpp_int exp, cpp_int p)
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

cpp_int modInv1(cpp_int a, cpp_int b)
{
    cpp_int x = 1, y = 0;
    while(b != 0)
    {
        cpp_int q = a / b;
        cpp_int rem = a % b;
        a = b;
        b = rem;

        cpp_int temp = x - q * y;
        x = y;
        y = temp;
    }
    if(x < 0) x += b;
    return x;
}

int main()
{
    cpp_int p("999999999999999999999999999999999841");
    cpp_int g = 2;
    cpp_int a = 127;
    cpp_int h = modExp1(g,a, p);
    cpp_int k = 53;
    cpp_int m = 123;

    cpp_int y1 = modExp1(g, k, p);
    cpp_int k_inv = modInv1(k, p - 1);
    cpp_int y2 = ((m - a * y1)*(k_inv) ) % (p-1);

    cout<<"Signature : (y1, y2): "<<y1<<" "<<y2<<endl;

    cpp_int left = (modExp1(y1, y2, p) * modExp1(h, y1, p)) % p;
    cpp_int right = (modExp1(g, m, p));

    cout<<"Verification: "<<left<<" "<<right<<endl;
    if(left == right){
        cout<<"Signature is valid: "<<endl;
    }
    else{
        cout<<"Signature is invalid: "<<endl;
    }

    return 0;
}
