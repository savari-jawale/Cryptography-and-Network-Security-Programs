#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate gcd (Greatest Common Divisor)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to compute modular inverse of e under modulo m using Extended Euclidean Algorithm
int modInverse(int e, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
        return 0;

    while (e > 1) {
        int q = e / m;
        int t = m;

        m = e % m;
        e = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

// Function to perform modular exponentiation
int modPower(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// RSA key generation
void generateRSAKeys(int &e, int &d, int &n) {
    int p = 3; // small prime number
    int q = 11; // small prime number
    n = p * q; // n = p * q
    int phi = (p - 1) * (q - 1); // Euler's Totient Function

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    e = 7; // Public exponent

    // Compute d such that d * e = 1 (mod phi)
    d = modInverse(e, phi);
}

// RSA Encryption
int encrypt(int message, int e, int n) {
    return modPower(message, e, n);
}

// RSA Decryption
int decrypt(int ciphertext, int d, int n) {
    return modPower(ciphertext, d, n);
}

int main() {
    int e, d, n;
    int message, ciphertext, decryptedMessage;

    // Generate RSA keys
    generateRSAKeys(e, d, n);

    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";

    // Original message
    cout << "Enter the message (numeric, less than " << n << "): ";
    cin >> message;

    // Encryption
    ciphertext = encrypt(message, e, n);
    cout << "Encrypted message (ciphertext): " << ciphertext << endl;

    // Decryption
    decryptedMessage = decrypt(ciphertext, d, n);
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}

