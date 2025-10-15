#include<bits/stdc++.h>
using namespace std;
#define ll long long

int p = 23;
int a = 1;
int b = 1;
pair<int, int> G = {13,7};

// Here y^2 = x^3 + x + 1 (mod 23)
// G = (13, 7)

int power(int base, int exp) {
    int res = 1;
    base %= p;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % p;
        base = (base * base) % p;
        exp /= 2;
    }
    return res;
}

int modInverse(int n) {
    return power(n, p - 2);
}

pair<int, int> pointAddition(pair<int, int>& P, pair<int, int>& Q){
    if(P.first == -1 && P.second == -1) return Q;
    if(Q.first == -1 && Q.second == -1) return P;

    int x1 = P.first;
    int y1 = P.second;
    int x2 = Q.first;
    int y2 = Q.second;

    int slope;
    if(x1 == x2 && y1 == y2){
        int numerator = (3 * x1 * x1 + a) % p;
        int denominator = (2 * y1) % p;
        slope = (numerator * modInverse(denominator)) % p;
    }else{
        int numerator = (y2 - y1);
        int denominator = (x2 - x1);
        slope = (numerator * modInverse(denominator)) % p;
    }
    
    if(slope < 0) slope += p;

    // Calculate the coordinates of the new point R(x3, y3)
    // x3 = (solpe^2 - x1 - x2) mod p
    int x3 = (slope * slope - x1 - x2) % p;
    if (x3 < 0) x3 += p;

    // y3 = (solpe * (x1 - x3) - y1) mod p
    int y3 = (slope * (x1-x3)-y1) % p;
    if (y3 < 0) y3 += p;

    return {x3, y3};
}

pair<int, int> scalarMultiply(int k, pair<int,int> & P){
    pair<int, int> result = {-1,-1};
    pair<int, int> addend = P;
    
    while(k > 0){
        if(k&1){
            result = pointAddition(result, addend);
        }
        addend = pointAddition(addend,addend);
        k /= 2;
    }
    return result;
}


int main(){
    cout << "Curve: y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")" << endl;
    cout << "Base Point G: (" << G.first << ", " << G.second << ")" << endl;
    cout << "--------------------------------------------------------" << endl;

    int alice_pr_key = 6;
    cout << "Alice's Private Key (secret): " << alice_pr_key << endl;
     // Alice computes her public key: P_A = private_key_A * G
    pair<int, int> alice_pb_key = scalarMultiply(alice_pr_key, G);
    cout << "Alice's Public Key (shared): (" << alice_pb_key.first << ", " << alice_pb_key.second << ")" << endl << endl;

    int bob_pr_key = 11;
    cout << "Bob's Private Key (secret): " << bob_pr_key << endl;

    pair<int, int> bob_pb_key = scalarMultiply(bob_pr_key, G);
    cout << "Bob's Public Key (shared): (" << bob_pb_key.first << ", " << bob_pb_key.second << ")" << endl;

    // --- Shared Secret Generation (ECDH) ---
    cout << "Both parties will now compute a shared secret without" << endl;
    cout << "exchanging their private keys." << endl << endl;

    // Alice computes the shared secret using her private key and Bob's public key
    // Secret_A = private_key_A * P_B
    pair<int, int> alice_shared_secret = scalarMultiply(alice_pr_key, bob_pb_key);
    cout << "Alice's computed shared secret: (" << alice_shared_secret.first << ", " << alice_shared_secret.second << ")" << endl;

    // Bob computes the shared secret using his private key and Alice's public key
    // Secret_B = private_key_B * P_A
    pair<int, int> bob_shared_secret = scalarMultiply(bob_pr_key, alice_pb_key);
    cout << "Bob's computed shared secret:   (" << bob_shared_secret.first << ", " << bob_shared_secret.second << ")" << endl << endl;

    // The shared secrets must be identical
    if (alice_shared_secret.first == bob_shared_secret.first && 
        alice_shared_secret.second == bob_shared_secret.second) {
        cout << "Success! Both parties have computed the same shared secret." << endl;
    } else {
        cout << "Error! Shared secrets do not match." << endl;
    }
    return 0;
}