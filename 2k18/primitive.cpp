#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll PowerMod(ll g, ll m, ll p){
	ll res = 1;
	for(int i=1; i<=m; i++){
		res = (res*g)%p;
	}

	res %= p;
	return res;
}

bool fun(ll p, ll g){
	map<ll, ll> mp;
	for(ll i=1; i<p; i++){
		ll x = PowerMod(g, i, p);
		cout<<i<<" "<<x<<endl;
		if(mp[x] > 0)
			return false;
		else
			mp[x]++;
	}

	return true;

}

int main(){
	ll prime = 7;
	ll g = 4;
	if(fun(prime, g)){
		cout<<"This is a primitive element"<<endl;
	}
	else{
		cout<<"This is not a primitive element"<<endl;
	}
	return 0;
}