#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Run-Length Encoding
string compressRLE(const string& data) {
    string result;
    int count = 1;

    for (size_t i = 1; i <= data.length(); ++i) {
        if (i < data.length() && data[i] == data[i - 1]) {
            count++;
        } else {
            result += to_string(count) + data[i - 1];
            count = 1;
        }
    }
    return result;
}

// Run-Length Decoding
string decompressRLE(const string& data) {
    string result;
    string countStr;

    for (size_t i = 0; i < data.length(); ++i) {
        if (isdigit(data[i])) {
            countStr += data[i];
        } else {
            if (countStr.empty()) {
                throw invalid_argument("Invalid compressed format: missing count before character '" + string(1, data[i]) + "'");
            }
            int count = stoi(countStr);
            result.append(count, data[i]);
            countStr.clear();
        }
    }

    return result;
}

int main() {
    char choice;
    cout << "Choose mode: (c)ompress or (d)ecompress: ";
    cin >> choice;

    if (choice == 'c') {
        ifstream inputFile("input.txt");
        if (!inputFile) {
            cerr << "❌ Cannot open input.txt\n";
            return 1;
        }

        string content((istreambuf_iterator<char>(inputFile)),
                       istreambuf_iterator<char>());
        inputFile.close();

        string compressed = compressRLE(content);

        ofstream outputFile("compressed.txt");
        if (!outputFile) {
            cerr << "❌ Cannot write compressed.txt\n";
            return 1;
        }

        outputFile << compressed;
        outputFile.close();

        cout << "✅ Compression done. Check compressed.txt\n";

    } else if (choice == 'd') {
        ifstream inputFile("compressed.txt");
        if (!inputFile) {
            cerr << "❌ Cannot open compressed.txt\n";
            return 1;
        }

        string content((istreambuf_iterator<char>(inputFile)),
                       istreambuf_iterator<char>());
        inputFile.close();

        try {
            string decompressed = decompressRLE(content);

            ofstream outputFile("decompressed.txt");
            if (!outputFile) {
                cerr << "❌ Cannot write decompressed.txt\n";
                return 1;
            }

            outputFile << decompressed;
            outputFile.close();

            cout << "✅ Decompression done. Check decompressed.txt\n";
        } catch (const exception& e) {
            cerr << "❌ Error: " << e.what() << '\n';
        }

    } else {
        cout << "❌ Invalid option. Use 'c' or 'd'.\n";
        return 1;
    }

    return 0;
}
