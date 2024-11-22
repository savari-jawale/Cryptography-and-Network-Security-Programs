#include <iostream>
#include <string>
using namespace std;

// Function to encrypt the plaintext using Vigenère Cipher
string encrypt(string plaintext, string key) {
    string ciphertext = "";
    int keyIndex = 0;
    
    for (int i = 0; i < plaintext.length(); i++) {
        char currentChar = plaintext[i];
        
        // If the character is alphabetic (A-Z, a-z)
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a'; // Determine whether the character is uppercase or lowercase
            int shift = (isupper(key[keyIndex % key.length()]) ? key[keyIndex % key.length()] - 'A' : key[keyIndex % key.length()] - 'a');
            ciphertext += char((currentChar - base + shift) % 26 + base);
            keyIndex++; // Move to the next character in the key
        } else {
            // Non-alphabetic characters remain unchanged
            ciphertext += currentChar;
        }
    }
    
    return ciphertext;
}

// Function to decrypt the ciphertext using Vigenère Cipher
string decrypt(string ciphertext, string key) {
    string plaintext = "";
    int keyIndex = 0;
    
    for (int i = 0; i < ciphertext.length(); i++) {
        char currentChar = ciphertext[i];
        
        // If the character is alphabetic (A-Z, a-z)
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a'; // Determine whether the character is uppercase or lowercase
            int shift = (isupper(key[keyIndex % key.length()]) ? key[keyIndex % key.length()] - 'A' : key[keyIndex % key.length()] - 'a');
            plaintext += char((currentChar - base - shift + 26) % 26 + base);
            keyIndex++; // Move to the next character in the key
        } else {
            // Non-alphabetic characters remain unchanged
            plaintext += currentChar;
        }
    }
    
    return plaintext;
}

int main() {
    string text, key;
    int choice;

    // Input the plaintext and key
    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the key: ";
    getline(cin, key);

    // Ensure the key is not empty
    if (key.empty()) {
        cout << "Key cannot be empty!" << endl;
        return 1;
    }

    cout << "Choose an option: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = encrypt(text, key);
        cout << "Encrypted message: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = decrypt(text, key);
        cout << "Decrypted message: " << decryptedText << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

