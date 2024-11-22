#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

// Function to perform the transposition based on the key order
string applyTransposition(string text, string key) {
    int numColumns = key.length();
    int numRows = (text.length() + numColumns - 1) / numColumns; // Round up to fit rows
    vector<vector<char>> grid(numRows, vector<char>(numColumns, 'X'));  // Fill with 'X' for padding

    // Fill the grid with the plaintext
    int k = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            if (k < text.length()) {
                grid[i][j] = text[k++];
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
    string result = "";
    for (const auto& pair : keyOrder) {
        int columnIndex = pair.first;
        for (int i = 0; i < numRows; i++) {
            result += grid[i][columnIndex];
        }
    }

    return result;
}

// Function to encrypt the plaintext using Double Transposition Cipher
string encryptDoubleTransposition(string plaintext, string key1, string key2) {
    // First transposition using the first key
    string firstTransposition = applyTransposition(plaintext, key1);

    // Second transposition using the second key
    string ciphertext = applyTransposition(firstTransposition, key2);

    return ciphertext;
}

// Function to decrypt the ciphertext using Double Transposition Cipher
string decryptDoubleTransposition(string ciphertext, string key1, string key2) {
    // First, reverse the second transposition using key2
    string firstReversed = applyTransposition(ciphertext, key2);

    // Then, reverse the first transposition using key1
    string plaintext = applyTransposition(firstReversed, key1);

    // Remove padding (X)
    plaintext.erase(remove(plaintext.begin(), plaintext.end(), 'X'), plaintext.end());

    return plaintext;
}

int main() {
    string text, key1, key2;
    int choice;

    cout << "Enter the plaintext: ";
    getline(cin, text);

    cout << "Enter the first key (a sequence of letters): ";
    getline(cin, key1);

    cout << "Enter the second key (a sequence of letters): ";
    getline(cin, key2);

    cout << "Choose an option: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = encryptDoubleTransposition(text, key1, key2);
        cout << "Encrypted message: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = decryptDoubleTransposition(text, key1, key2);
        cout << "Decrypted message: " << decryptedText << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

