#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Function to find the modular inverse of a number modulo 26
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;  // In case the modular inverse doesn't exist (shouldn't happen if the key matrix is invertible)
}

// Function to find the determinant of a 2x2 matrix
int determinant(int matrix[2][2], int m) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % m;
}

// Function to find the inverse of a 2x2 matrix modulo 26
bool inverseMatrix(int matrix[2][2], int m, int inverse[2][2]) {
    int det = determinant(matrix, m);
    int detInv = modInverse(det, m);

    if (detInv == -1) {
        return false; // Inverse doesn't exist if determinant is not invertible modulo 26
    }

    inverse[0][0] = (matrix[1][1] * detInv) % m;
    inverse[0][1] = (-matrix[0][1] * detInv) % m;
    inverse[1][0] = (-matrix[1][0] * detInv) % m;
    inverse[1][1] = (matrix[0][0] * detInv) % m;

    // Making sure all values are positive modulo 26
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += m;
            }
        }
    }
    return true;
}

// Function to convert a string to its numerical equivalent (A=0, B=1, ..., Z=25)
vector<int> stringToVector(string text) {
    vector<int> result;
    for (char c : text) {
        if (isalpha(c)) {
            result.push_back(toupper(c) - 'A');
        }
    }
    return result;
}

// Function to convert a vector of integers back to a string
string vectorToString(const vector<int>& vec) {
    string result = "";
    for (int v : vec) {
        result += char(v + 'A');
    }
    return result;
}

// Function to multiply a 2x2 matrix with a 2x1 vector
vector<int> multiplyMatrixVector(int matrix[2][2], vector<int>& vec, int m) {
    vector<int> result(2);
    for (int i = 0; i < 2; i++) {
        result[i] = 0;
        for (int j = 0; j < 2; j++) {
            result[i] = (result[i] + matrix[i][j] * vec[j]) % m;
        }
    }
    return result;
}

// Hill Cipher encryption function
string encrypt(string plaintext, int key[2][2], int m) {
    string ciphertext = "";
    vector<int> vec = stringToVector(plaintext);

    // Pad plaintext if necessary to make it even length
    if (vec.size() % 2 != 0) {
        vec.push_back(23); // 'X' as filler
    }

    // Encrypt in blocks of 2 letters
    for (size_t i = 0; i < vec.size(); i += 2) {
        vector<int> block = {vec[i], vec[i + 1]};
        vector<int> encryptedBlock = multiplyMatrixVector(key, block, m);
        ciphertext += vectorToString(encryptedBlock);
    }

    return ciphertext;
}

// Hill Cipher decryption function
string decrypt(string ciphertext, int key[2][2], int m) {
    string plaintext = "";
    vector<int> vec = stringToVector(ciphertext);
    int inverseKey[2][2];

    // Find inverse of the key matrix
    if (!inverseMatrix(key, m, inverseKey)) {
        cout << "Key matrix is not invertible." << endl;
        return "";
    }

    // Decrypt in blocks of 2 letters
    for (size_t i = 0; i < vec.size(); i += 2) {
        vector<int> block = {vec[i], vec[i + 1]};
        vector<int> decryptedBlock = multiplyMatrixVector(inverseKey, block, m);
        plaintext += vectorToString(decryptedBlock);
    }

    return plaintext;
}

int main() {
    string plaintext;
    int key[2][2];
    int choice;

    cout << "Enter the plaintext (only alphabetic characters): ";
    getline(cin, plaintext);

    cout << "Enter the key matrix (2x2):" << endl;
    cout << "Enter key[0][0]: ";
    cin >> key[0][0];
    cout << "Enter key[0][1]: ";
    cin >> key[0][1];
    cout << "Enter key[1][0]: ";
    cin >> key[1][0];
    cout << "Enter key[1][1]: ";
    cin >> key[1][1];

    cout << "Choose an option: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string encrypted = encrypt(plaintext, key, 26);
        cout << "Encrypted message: " << encrypted << endl;
    } else if (choice == 2) {
        string decrypted = decrypt(plaintext, key, 26);
        cout << "Decrypted message: " << decrypted << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

