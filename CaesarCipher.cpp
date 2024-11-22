#include <iostream>
#include <string>
using namespace std;

// Function to encrypt a message using Caesar Cipher
string encrypt(string text, int shift) {
    string result = "";
    
    // Loop through each character in the text
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        
        // Encrypt uppercase letters
        if (isupper(ch)) {
            result += char(int(ch + shift - 65) % 26 + 65);
        }
        // Encrypt lowercase letters
        else if (islower(ch)) {
            result += char(int(ch + shift - 97) % 26 + 97);
        }
        // Keep non-alphabetic characters unchanged
        else {
            result += ch;
        }
    }
    
    return result;
}

// Function to decrypt a message using Caesar Cipher
string decrypt(string text, int shift) {
    return encrypt(text, 26 - shift); // Decrypt is just the inverse of encryption
}

int main() {
    string text;
    int shift;
    int choice;

    // Input the message and shift value
    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the shift value: ";
    cin >> shift;

    // Ensure the shift is between 0 and 25
    shift = shift % 26;

    cout << "Choose an option: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string encrypted = encrypt(text, shift);
        cout << "Encrypted message: " << encrypted << endl;
    } else if (choice == 2) {
        string decrypted = decrypt(text, shift);
        cout << "Decrypted message: " << decrypted << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

