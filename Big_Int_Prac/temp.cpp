#include <bits/stdc++.h>
using namespace std;
#define ll long long


ll modExp(ll a, ll b, ll n){
    if(b==0) return 1;

    if(b&1){
        return a * (modExp(a, b/2, n) * modExp(a, b/2, n)) % n;
    }
    return (modExp(a, b/2, n) * modExp(a, b/2, n)) % n;
}

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
    ll p = 23;
    ll g = 5;
    ll x = 6;
    ll y = modExp(g,x,p);//g^x%p
    cout<<"Public key(p,g,y):"<<p<<" "<<g<<" "<<y<<endl;
    cout<<"Private key(x):"<<x<<endl;

    ll msg = 13;
    ll k = 15;

    //Encryption
    ll c1 = modExp(g,k,p);
    ll c2 = msg * modExp(y,k,p) % p;

    cout<<"Ciphertext: "<<c1<<" "<<c2<<endl;

    //Decryption
    ll s = modExp(c1,x,p);
    ll s_inv = modInverse(s,p);
    ll dec = (c2 * s_inv) % p;
    cout<<"Decrypted msg: "<<dec<<endl;


    
    return 0;
}