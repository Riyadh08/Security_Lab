//RSA Product Cipher

#include <bits/stdc++.h>
using namespace std;
#define ll long long 

ll gcd(ll a, ll b){
    if(b==0) return a;
    
    return gcd(b, a%b);
}

ll modInverse(ll e, ll phi){
    ll a = e, b = phi;
    ll x = 1, y = 0;

    while(b != 0){
        ll q = a / b;
        ll rem = a % b;  // separate remainder
        a = b;
        b = rem;

        ll temp = x - q * y; // separatve temp for coefficient
        x = y;
        y = temp;
    }
    if(a != 1) return -1;  // inverse doesn't exist is gcd != 1
    if(x < 0) x += phi;  // make inverse pasitive
    return x;
}

ll powMod(ll base, ll exp, ll n){
    ll res = 1;
    base = base % n;
    while(exp > 0){
        if(exp & 1) res = (res * base) % n;
        exp >>= 1;
        base = (base * base) % n;
    }
    return res;
}


int main() {
    ll p,q;
    cin>>p>>q;

    ll n = p*q;
    ll phi = (p-1)*(q-1);

    ll e = 2;
    while(gcd(phi, e) != 1) e++;
    cout<<"Public Key (e) : "<<e<<endl;
    cout<<"Phi_n: "<<phi<<endl;
    ll d = modInverse(e, phi);
    cout<<"Private Key (d): "<<d<<endl;
    
    ll ms1, ms2;
    cin>>ms1>>ms2;
    cout<<"Product of Plaintext: "<<(ms1*ms2) % n<<endl;
    ll c1 = powMod(ms1, e, n);
    ll c2 = powMod(ms2, e, n);
    cout<<c1<<" "<<c2<<endl;
    ll c = (c1 * c2) % n;

    cout<<"Cipher text: "<<c<<endl;

    ll dec = powMod(c, d, n);
    cout<<"Decrepted ms: "<<dec<<endl;

    return 0;
}