//RSA Multiple Private key calculation and attack

#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

ll powMod(ll base, ll exp, ll n){
    ll res = 1;
    base = base % n;

    while(exp > 0){

        if(exp &1) res = (res * base) % n;

        exp >>= 1;
        base = (base * base) % n;

    }
    return res;
}

ll modInv(ll e, ll phi)
{
    ll a = e, b = phi;
    ll x = 1, y = 0;

    while(b != 0)
    {
        ll q = a / b;
        ll rem = a % b;

        a = b;
        b = rem;

        ll temp = x - y * q;
        x = y;
        y = temp;
    }
    if(x < 0) x += phi;
    return x;
}

int main() {
    ll p = 19, q = 23;
    // cin>>p>>q;
    ll n = p * q;

    ll phi = (p-1) * (q-1);
    ll e = 2;
    while(gcd(e, phi) != 1) e++;
    cout<<"public key (e): "<<e<<endl;
    ll d = modInv(e, phi);
    cout<<"private key (d): "<<d<<endl;

    ll cnt = 0;
    ll dd[5];
    for(ll i=0; i < phi; i++){
        if((1 + i * phi) % e == 0){
            dd[cnt] = (1 + i * phi) / e;
            cnt++;
            if(cnt > 4) break;
        }
    }
    for(auto it : dd) cout<<it<<" ";
    cout<<endl;

    ll ms = 12;
    // cin>>ms;
    ll c1 = powMod(ms, e, n);
    cout<<"Ciphertext: "<<c1<<endl;
    ll dec = powMod(c1, d, n);
    cout<<"Decrypted using d: "<<dec<<endl;

    for(ll i=2; i<n; i++){
       // cout<<"ryad,=== "<<i<<endl;
        if(ms == powMod(c1, i, n)){
            cout<<"Decrypted: "<<ms<<endl;
            cout<<"Iteration is: "<<i<<endl;
            break;
        }
    }
    
    return 0;
}