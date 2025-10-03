#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll modExp(ll base, ll exp, ll n){
    ll res = 1;
    base = base % n;
    while(exp){
        if(exp & 1) res = (res * base) % n;
        exp >>= 1;
        base = (base * base) % n;

    }
    return res;
}

ll modInverse(ll a, ll b){
    ll x0 = 1, x1 = 0;

    while(b != 0){
        ll q = a/b;
        ll rem = a%b;

        a = b;
        b = rem;

        ll temp = x0 - q*x1;
        x0 = x1;
        x1 = temp;
    }
    if (a != 1) return -1;
    if(x0 < 0) x0 += b;
    return x0;

}

int main() {
    //5 digit prime p = 10007
    ll p = 23;
    ll g = 5;
    ll a = 6; // private key
    ll y = modExp(g,a,p); // public kye y = g^a % p

    cout<<"Public Keys: (p,g,y): "<<p<<" "<<g<<" "<<y<<endl;
    cout<<"Prive Key: (a): "<<a<<endl;

    ll m = 13; // message
    ll k = 15; // Random secret integer

    ll c1 = modExp(g,k, p);
    ll c2 = (m*modExp(y,k,p)) % p;
    cout<<"Ciphertext: "<<c1<<" "<<c2<<endl;

    ll s = modExp(c1,a,p);
    ll s_inv = modExp(s,p-2,p);
    ll dec = (c2 * s_inv) % p;

    cout<<"decrypted message: "<<dec<<endl;


    
    return 0;
}