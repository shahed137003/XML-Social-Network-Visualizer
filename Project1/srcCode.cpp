#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to read file content
string readFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}


// Function to write file content
void writeFile(const string& fileName, const string& content) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to write to file " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    file << content;
    file.close();
}

// Function to find the most frequent pair in the text
pair<string, int> findMostFrequentPair(const string& text) {
    unordered_map<string, int> pairFrequency;
    for (size_t i = 0; i < text.size() - 1; ++i) {
        string pair = text.substr(i, 2);
        pairFrequency[pair]++;
    }

    pair<string, int> mostFrequent = { "", 0 };
    for (const auto& entry : pairFrequency) {
        if (entry.second > mostFrequent.second) {
            mostFrequent = entry;
        }
    }
    return mostFrequent;
}

// Function to compress the input using BPE
string compress(const string& input, unordered_map<string, string>& encodingTable) {
    string compressed = input;
    char placeholder = 128; // Start with the first unused byte
    while (true) {
        auto mostFrequentPair = findMostFrequentPair(compressed);
        if (mostFrequentPair.second < 2) break; // Stop if no pair is frequent

        string pair = mostFrequentPair.first;
        string placeholderStr(1, placeholder);

        // Replace the pair with the placeholder
        size_t pos = 0;
        while ((pos = compressed.find(pair, pos)) != string::npos) {
            compressed.replace(pos, 2, placeholderStr);
            pos += placeholderStr.size();
        }

        encodingTable[placeholderStr] = pair;
        placeholder++;
    }
    return compressed;
}

// Function to decompress the text using the encoding table
string decompress(const string& input, const unordered_map<string, string>& encodingTable) {
    string decompressed = input;
    for (const auto& entry : encodingTable) {
        const string& placeholder = entry.first;
        const string& pair = entry.second;

        size_t pos = 0;
        while ((pos = decompressed.find(placeholder, pos)) != string::npos) {
            decompressed.replace(pos, placeholder.size(), pair);
            pos += pair.size();
        }
    }
    return decompressed;
}

// Main function for command-line operations
int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage:\n"
            << argv[0]
            << "  Compress: xml_editor compress -i input_file.xml -o output_file.comp\n"
            << "  Decompress: xml_editor decompress -i input_file.comp -o output_file.xml\n";
        return EXIT_FAILURE;
    }

    string operation = argv[1];
    string inputFile;
    string outputFile;

    for (int i = 2; i < argc; i += 2) {
        string option = argv[i];
        string value = argv[i + 1];

        if (option == "-i") {
            inputFile = value;
        }
        else if (option == "-o") {
            outputFile = value;
        }
        else {
            cerr << "Unknown option: " << option << endl;
            return EXIT_FAILURE;
        }
    }

    if (operation == "compress") {
        string inputContent = readFile(inputFile);
        unordered_map<string, string> encodingTable;

        string compressedContent = compress(inputContent, encodingTable);

        // Save compressed content
        writeFile(outputFile, compressedContent);

        // Save encoding table
        string encodingTableFile = outputFile + ".table";
        ofstream tableFile(encodingTableFile);
        for (const auto& entry : encodingTable) {
            tableFile << entry.first << " " << entry.second << "\n";
        }
        tableFile.close();

        cout << "Compression completed. Table saved as: " << encodingTableFile << endl;

    }
    else if (operation == "decompress") {
        string compressedContent = readFile(inputFile);

        // Load encoding table
        string encodingTableFile = inputFile + ".table";
        ifstream tableFile(encodingTableFile);
        if (!tableFile.is_open()) {
            cerr << "Error: Encoding table file not found: " << encodingTableFile << endl;
            return EXIT_FAILURE;
        }

        unordered_map<string, string> encodingTable;
        string placeholder, pair;
        while (tableFile >> placeholder >> pair) {
            encodingTable[placeholder] = pair;
        }
        tableFile.close();

        string decompressedContent = decompress(compressedContent, encodingTable);

        // Save decompressed content
        writeFile(outputFile, decompressedContent);

        cout << "Decompression completed." << endl;

    }
    else {
        cerr << "Unknown operation: " << operation << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
