// RSA Signature
#include <bits/stdc++.h>
using namespace std;
using ll  = long long;

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

        ll temp = x - q * y;
        x = y;
        y = temp;
    }
    if(x < 0) x += phi;
    return x;
}

ll modExp(ll base, ll exp, ll n)
{
    ll res = 1;

    while(exp > 0)
    {
        if(exp & 1) res = (res * base) % n;
        base = (base * base) % n;
        exp /= 2;
    }
    return res;
}
int main()
{
    ll p = 19, q = 23;
    ll n = p * q;
    ll phi = (p-1) * (q-1);

    ll ms = 12;
    ll e = 2;
    while(__gcd(e, phi) != 1) e++;

    ll d = modInv(e, phi);
    cout<<"e, d: " <<e<< " "<<d<<endl;

    //Sign in using pvt key
    ll sig = modExp(ms, d, n);
    cout<<"signature: "<<sig<<endl;

    ll veri = modExp(sig, e, n);
    cout<<"veri: "<<veri<<endl;

    if(ms = veri) cout<<"Signature is valid: "<<endl;
    else cout<<"signature is not valid: "<<endl;

    return 0;
}
