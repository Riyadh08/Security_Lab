#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b){
    if(b==0) return a;
    return gcd(b, a%b);
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


ll powerMod(ll base, ll exp, ll n){
    ll res = 1;
    base = base % n;
    while(exp > 0){   // FIXED
        if(exp & 1) res = (res * base) % n;
        base = (base * base) % n;
        exp >>= 1;
    }
    return res;
}

int main() {
    ll p,q;
    cin>>p>>q;
    ll n = p*q;
    ll phi = (p-1) * (q-1);

    ll ms1, ms2;
    cin>>ms1>>ms2;
    cout<<"ms1 * ms2: "<<(ms1 * ms2) % n<<endl;

    ll e = 2;
    while(gcd(phi,e) != 1) e++;
    ll d = modInverse(e, phi);  // FIXED

    cout<<"Public Key: "<<e<<endl;
    cout<<"Private Key: "<<d<<endl;

    ll enc1 = powerMod(ms1, e, n);
    ll enc2 = powerMod(ms2, e, n);
    ll enc = (enc1 * enc2) % n;
    cout<<"Encrypted ms: "<<enc<<endl;

    // ll dec1 = powerMod(enc1, d, n);
    // ll dec2 = powerMod(enc2, d, n);
    // ll dec = (dec1 * dec2) % n;
    ll dec = powerMod(enc, d, n);
    cout<<"Decrypted ms: "<<dec<<endl;

    return 0;
}


