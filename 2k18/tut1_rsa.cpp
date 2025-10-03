#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b){
    if(b==0) return a;

    return gcd(b,a%b);
}

ll modInverse(ll e, ll phi){
    for(ll d=1; d<phi; d++){
        if((d*e) %phi==1){
            return d;
        }
    }
    return -1;
}

ll powerMod(ll msg, ll exp, ll n){
    ll result = 1;
    msg = msg % n;
    
    while(exp > 0){
        if(exp % 2 == 1){
            result = (result * msg) % n;
        }
        exp = exp >> 1;
        msg = (msg * msg) % n;
        // msg, msg^2, msg^4,msg^8,msg^16 and so on
    }
    return result;
}

int main(){

    ll p,q;
    cin>>p>>q;
    ll n = p*q;
    ll phi = (p-1)*(q-1);

    // e -> public key
    ll e = 2;
    while(gcd(phi,e) != 1) e++;
    
    //d -> private key
    ll d = modInverse(e,phi);

    cout<<"Public key: "<<e<<endl;
    cout<<"Private key: "<<d<<endl;

    ll msg;
    cin>>msg;

    ll encrypted = powerMod(msg,e,n);
    cout<<"Enctypted msg: "<<encrypted<<endl;

    ll decrypted = powerMod(encrypted, d, n);
    cout<<"Decrypted msg: "<<decrypted<<endl;
    return 0;
}

/*

e holo choto molik shankha ja phi er shathe coprime.
Generally,
e=3, 17 & 65537.
tai gcd(3, phi) = 1 dhore co-prime check kora hoche.
5 digit prime numbers:

p = 10007
q = 10009
msg = 100163

*/