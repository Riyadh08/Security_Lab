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
        base = base * base;

    }
    return res;
}


int main() {
    ll p, q;
    cin>>p>>q;
    ll n = p * q;

    ll phi = (p-1) * (q-1);
    ll e = 2;
    while(gcd(e, phi) != 1) e++;
    cout<<"phublic key (e): "<<e<<endl;

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

    ll ms;
    cin>>ms;
    ll c1 = powMod(ms, e, n);

    for(ll i=2; i<n; i++){
        if(ms == powMod(c1, i, n)){
            cout<<"Decrypted: "<<ms<<endl;
            cout<<"Iteration is: "<<i<<endl;
            break;
        }
    }


    
    return 0;
}