#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to encrypt the message using the Rail Fence Cipher
string encryptRailFence(string text, int rails) {
    if (rails == 1) {
        return text; // No encryption needed if only one rail
    }
    
    vector<string> rail(rails);  // Create a vector of strings, one for each rail
    int row = 0;
    bool goingDown = false;
    
    // Build the zigzag pattern by writing characters into the rail array
    for (char c : text) {
        rail[row] += c;  // Add the current character to the rail
        
        // Change direction at the top and bottom rails
        if (row == 0 || row == rails - 1) {
            goingDown = !goingDown;
        }
        
        // Move to the next rail
        row += (goingDown ? 1 : -1);
    }
    
    // Read the rail array to create the encrypted message
    string ciphertext = "";
    for (const string& r : rail) {
        ciphertext += r;
    }
    
    return ciphertext;
}

// Function to decrypt the message using the Rail Fence Cipher
string decryptRailFence(string ciphertext, int rails) {
    if (rails == 1) {
        return ciphertext; // No decryption needed if only one rail
    }
    
    // Create an array to store the rail fence pattern
    vector<vector<char>> rail(rails, vector<char>(ciphertext.length(), '\n'));
    
    int index = 0;
    int row = 0;
    bool goingDown = false;
    
    // First, place the ciphertext characters in the zigzag pattern
    for (int col = 0; col < ciphertext.length(); col++) {
        rail[row][col] = '*';  // Mark the positions to fill
        
        // Change direction at the top and bottom rails
        if (row == 0 || row == rails - 1) {
            goingDown = !goingDown;
        }
        
        // Move to the next rail
        row += (goingDown ? 1 : -1);
    }
    
    // Fill the rail fence pattern with the ciphertext characters
    index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < ciphertext.length(); j++) {
            if (rail[i][j] == '*' && index < ciphertext.length()) {
                rail[i][j] = ciphertext[index++];
            }
        }
    }
    
    // Read the pattern vertically to get the decrypted text
    string plaintext = "";
    row = 0;
    goingDown = false;
    for (int col = 0; col < ciphertext.length(); col++) {
        plaintext += rail[row][col];
        
        // Change direction at the top and bottom rails
        if (row == 0 || row == rails - 1) {
            goingDown = !goingDown;
        }
        
        // Move to the next rail
        row += (goingDown ? 1 : -1);
    }
    
    return plaintext;
}

int main() {
    string text;
    int rails, choice;
    
    cout << "Enter the message: ";
    getline(cin, text);
    
    cout << "Enter the number of rails: ";
    cin >> rails;
    
    cout << "Choose an option: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        string encryptedText = encryptRailFence(text, rails);
        cout << "Encrypted message: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = decryptRailFence(text, rails);
        cout << "Decrypted message: " << decryptedText << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}

