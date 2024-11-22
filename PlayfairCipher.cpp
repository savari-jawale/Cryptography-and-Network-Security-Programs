#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

// Function to format the input (remove spaces, replace J with I, and split into digraphs)
string formatInput(string input) {
    string formatted = "";
    
    // Remove spaces and convert 'J' to 'I'
    for (char& ch : input) {
        if (isalpha(ch)) {
            formatted += toupper(ch);
        }
    }

    // Replace 'J' with 'I' as per the Playfair Cipher rules
    for (int i = 0; i < formatted.size(); i++) {
        if (formatted[i] == 'J') {
            formatted[i] = 'I';
        }
    }

    // Split into digraphs
    string digraphs = "";
    for (int i = 0; i < formatted.length(); i++) {
        if (i + 1 < formatted.length() && formatted[i] != formatted[i + 1]) {
            digraphs += formatted[i];
            digraphs += formatted[i + 1];
            i++;
        } else {
            digraphs += formatted[i];
            digraphs += 'X';  // If two same letters appear, add 'X'
        }
    }

    return digraphs;
}

// Function to create the Playfair matrix using the keyword
vector<vector<char>> createMatrix(string keyword) {
    vector<vector<char>> matrix(5, vector<char>(5));
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";  // 'J' is omitted
    string key = "";

    // Remove duplicates from the keyword
    for (char ch : keyword) {
        if (key.find(ch) == string::npos && isalpha(ch)) {
            key += toupper(ch);
        }
    }

    // Fill the matrix with the keyword and the rest of the alphabet
    for (char ch : alphabet) {
        if (key.find(ch) == string::npos) {
            key += ch;
        }
    }

    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = key[index++];
        }
    }

    return matrix;
}

// Function to find the position of a character in the matrix
pair<int, int> findPosition(char ch, vector<vector<char>>& matrix) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1); // This should never be reached if the input is valid
}

// Function to encrypt the message
string encrypt(string digraphs, vector<vector<char>>& matrix) {
    string ciphertext = "";
    for (int i = 0; i < digraphs.length(); i += 2) {
        char first = digraphs[i];
        char second = digraphs[i + 1];
        pair<int, int> pos1 = findPosition(first, matrix);
        pair<int, int> pos2 = findPosition(second, matrix);

        // Case 1: Same row
        if (pos1.first == pos2.first) {
            ciphertext += matrix[pos1.first][(pos1.second + 1) % 5];
            ciphertext += matrix[pos2.first][(pos2.second + 1) % 5];
        }
        // Case 2: Same column
        else if (pos1.second == pos2.second) {
            ciphertext += matrix[(pos1.first + 1) % 5][pos1.second];
            ciphertext += matrix[(pos2.first + 1) % 5][pos2.second];
        }
        // Case 3: Rectangle case
        else {
            ciphertext += matrix[pos1.first][pos2.second];
            ciphertext += matrix[pos2.first][pos1.second];
        }
    }
    return ciphertext;
}

// Function to decrypt the message
string decrypt(string digraphs, vector<vector<char>>& matrix) {
    string plaintext = "";
    for (int i = 0; i < digraphs.length(); i += 2) {
        char first = digraphs[i];
        char second = digraphs[i + 1];
        pair<int, int> pos1 = findPosition(first, matrix);
        pair<int, int> pos2 = findPosition(second, matrix);

        // Case 1: Same row
        if (pos1.first == pos2.first) {
            plaintext += matrix[pos1.first][(pos1.second + 4) % 5];
            plaintext += matrix[pos2.first][(pos2.second + 4) % 5];
        }
        // Case 2: Same column
        else if (pos1.second == pos2.second) {
            plaintext += matrix[(pos1.first + 4) % 5][pos1.second];
            plaintext += matrix[(pos2.first + 4) % 5][pos2.second];
        }
        // Case 3: Rectangle case
        else {
            plaintext += matrix[pos1.first][pos2.second];
            plaintext += matrix[pos2.first][pos1.second];
        }
    }
    return plaintext;
}

int main() {
    string text, key;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the keyword: ";
    getline(cin, key);

    // Format the input text
    string digraphs = formatInput(text);

    // Create the Playfair cipher matrix
    vector<vector<char>> matrix = createMatrix(key);

    cout << "Choose an option: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = encrypt(digraphs, matrix);
        cout << "Encrypted message: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = decrypt(digraphs, matrix);
        cout << "Decrypted message: " << decryptedText << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

