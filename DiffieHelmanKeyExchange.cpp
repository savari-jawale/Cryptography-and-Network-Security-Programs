#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate (base^exponent) % mod using binary exponentiation
long long modPower(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;  // In case base is greater than mod
    while (exponent > 0) {
        if (exponent % 2 == 1) {  // If exponent is odd
            result = (result * base) % mod;
        }
        exponent = exponent >> 1;  // Divide exponent by 2
        base = (base * base) % mod;  // Square the base
    }
    return result;
}

int main() {
    long long p, g, a, b;
    
    cout << "Enter a large prime number p: ";
    cin >> p;
    cout << "Enter a primitive root g (base): ";
    cin >> g;

    // Alice's private key 'a' and Bob's private key 'b'
    cout << "Enter Alice's private key (a): ";
    cin >> a;
    cout << "Enter Bob's private key (b): ";
    cin >> b;

    // Calculate public keys
    long long A = modPower(g, a, p);  // Alice's public key
    long long B = modPower(g, b, p);  // Bob's public key

    cout << "Alice's public key (A): " << A << endl;
    cout << "Bob's public key (B): " << B << endl;

    // Now both Alice and Bob calculate the shared secret
    long long sharedSecretAlice = modPower(B, a, p);  // Alice calculates shared secret
    long long sharedSecretBob = modPower(A, b, p);    // Bob calculates shared secret

    cout << "Alice's calculated shared secret: " << sharedSecretAlice << endl;
    cout << "Bob's calculated shared secret: " << sharedSecretBob << endl;

    // Verify that both Alice and Bob have the same shared secret
    if (sharedSecretAlice == sharedSecretBob) {
        cout << "Shared secret is successfully established: " << sharedSecretAlice << endl;
    } else {
        cout << "Shared secret does not match!" << endl;
    }

    return 0;
}

