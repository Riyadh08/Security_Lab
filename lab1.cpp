#include <bits/stdc++.h>
using namespace std;

int main() {
    string msg;
    // cout << "Enter message (UPPERCASE only): ";
    cin >> msg;

    string key;
    // cout << "Enter numeric key (e.g. 4231): ";
    cin >> key;

    int cols = key.size();
    int rows = ceil((msg.size() * 1.0) / cols);

    // Step 1: Fill matrix row-wise
    vector<vector<char>> arr(rows, vector<char>(cols, '*'));
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (k < msg.size())
                arr[i][j] = msg[k];
            else
                arr[i][j] = '*';
            k++;
        }
    }

    cout << "\nMatrix (row-wise filled):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // Step 2: Encryption (read column by key order)
    string cipher = "";
    for (int c = 0; c < cols; c++) {
        int colIndex = (key[c] - '0') - 1; // key is 1-based
        for (int r = 0; r < rows; r++) {
            cipher += arr[r][colIndex];
        }
    }

    cout << "\nCipher Text: " << cipher << endl;

    // Step 3: Fill matrix column-wise for decryption
    vector<vector<char>> arr2(rows, vector<char>(cols, '*'));
    int idx = 0;
    for (int c = 0; c < cols; c++) {
        int colIndex = (key[c] - '0') - 1;
        for (int r = 0; r < rows; r++) {
            arr2[r][colIndex] = cipher[idx++];
        }
    }

    cout << "\nMatrix after filling cipher (for decryption):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr2[i][j] << " ";
        }
        cout << endl;
    }

    // Step 4: Decryption (read row-wise)
    string plain = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr2[i][j] != '*')
                plain += arr2[i][j];
        }
    }

    cout << "\nDecrypted Plain Text: " << plain << endl;

    return 0;
}


/*

ABCDEFGHIJKLMNO
4231

ABCDEFGHIJKLMNO
1234

*/