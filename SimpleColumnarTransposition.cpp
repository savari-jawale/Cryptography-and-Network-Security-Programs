#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function to encrypt the plaintext using the Columnar Transposition Cipher
string encryptColumnarTransposition(string plaintext, string key) {
    int numColumns = key.length();
    int numRows = (plaintext.length() + numColumns - 1) / numColumns; // round up to fit rows
    vector<vector<char>> grid(numRows, vector<char>(numColumns, 'X'));  // Fill with 'X' for padding

    // Fill the grid with the plaintext
    int k = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            if (k < plaintext.length()) {
                grid[i][j] = plaintext[k++];
            }
        }
    }

    // Create a vector of pairs (index, character) based on the key
    vector<pair<int, char>> keyOrder(numColumns);
    for (int i = 0; i < numColumns; i++) {
        keyOrder[i] = {i, key[i]};
    }

    // Sort the key order based on the alphabetical order of the key
    sort(keyOrder.begin(), keyOrder.end(), [](const pair<int, char>& a, const pair<int, char>& b) {
        return a.second < b.second;
    });

    // Read columns in the new order defined by the sorted key
    string ciphertext = "";
    for (const auto& pair : keyOrder) {
        int columnIndex = pair.first;
        for (int i = 0; i < numRows; i++) {
            ciphertext += grid[i][columnIndex];
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using the Columnar Transposition Cipher
string decryptColumnarTransposition(string ciphertext, string key) {
    int numColumns = key.length();
    int numRows = ciphertext.length() / numColumns;
    vector<vector<char>> grid(numRows, vector<char>(numColumns, 'X'));

    // Create a vector of pairs (index, character) based on the key
    vector<pair<int, char>> keyOrder(numColumns);
    for (int i = 0; i < numColumns; i++) {
        keyOrder[i] = {i, key[i]};
    }

    // Sort the key order based on the alphabetical order of the key
    sort(keyOrder.begin(), keyOrder.end(), [](const pair<int, char>& a, const pair<int, char>& b) {
        return a.second < b.second;
    });

    // Fill the grid with the ciphertext characters in the order of the sorted key
    int index = 0;
    for (const auto& pair : keyOrder) {
        int columnIndex = pair.first;
        for (int i = 0; i < numRows; i++) {
            grid[i][columnIndex] = ciphertext[index++];
        }
    }

    // Read the grid row by row to get the decrypted message
    string plaintext = "";
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            plaintext += grid[i][j];
        }
    }

    // Remove padding (X) from the decrypted message
    plaintext.erase(remove(plaintext.begin(), plaintext.end(), 'X'), plaintext.end());

    return plaintext;
}

int main() {
    string plaintext, key;
    int choice;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    
    cout << "Enter the key (a sequence of letters): ";
    getline(cin, key);

    cout << "Choose an option: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        string encryptedText = encryptColumnarTransposition(plaintext, key);
        cout << "Encrypted message: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = decryptColumnarTransposition(plaintext, key);
        cout << "Decrypted message: " << decryptedText << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

