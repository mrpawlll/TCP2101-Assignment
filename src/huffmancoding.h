#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Huffman tree node ( in project, is listed in entities.h)
struct Node {
    string word;
    int frequency;
    Node* left;
    Node* right;

    Node(string word, int frequency) {
        this->word = word;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

// Custom comparator for priority queue (in project, listed in utils.h)
struct Compare {
    bool operator()(Node* left, Node* right) {
        string L = left->word;
        string R = right->word;

        if(left->frequency == right->frequency){
            if(L.length() == R.length()){
                return R.compare(left->word);
            }else{
                return L.length() > R.length();
            }
        }else{
            return left->frequency > right->frequency;
        }
    }
};

// Traverse Huffman tree and generate codes
void generateCodes(Node* root, string code, unordered_map<string, string>& codes) {
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->word] = code;
        return;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

string encodeWords(const string& text, const unordered_map<string, string>& codes) {
    string encodedText;
    for (char ch : text) {
        string word(1, ch);
        if (codes.find(word) != codes.end()) {
            encodedText += codes.at(word);
        } else {
            cerr << "Error: Encoding failed. Code not found for character: " << ch << endl;
            return "";
        }
    }
    return encodedText;
}

// Decode encoded text using Huffman codes
string decodeText(const string& encodedText, Node* root) {
    string decodedText;
    Node* current = root;
    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->word;
            current = root;
        }
    }
    return decodedText;
}

// Build Huffman tree
Node* buildHuffmanTree(const unordered_map<string, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (const auto& entry : frequencies) {
        pq.push(new Node(entry.first, entry.second));
    }

    int initialSize = pq.size();
    while (pq.size() > 1) {
        Node* left = pq.top();
        // cout<<"Left:"<<left->word<<"("<<left->frequency<<")"<<endl;
        pq.pop();
        Node* right = pq.top();
        // cout<<"Right:"<<right->word<<"("<<right->frequency<<")"<<endl;
        pq.pop();

        string parentName = left->word + right->word;
        int sumFrequency = left->frequency + right->frequency;
        Node* parent = new Node(parentName, sumFrequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
        // cout<<endl;
    }

    return pq.top();
}

// Perform Huffman coding on the input text
void huffmanEncoding(const string& inputFile, const string& outputFile,bool q5) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Error: Unable to open input file." << endl;
        return;
    }

    // Count word frequencies
    unordered_map<string, int> frequencies;
    string line;
    int lineNumber = 1;
    int totalLines;
    string lastLine;

    while (getline(input, line)) {
        if (lineNumber == 1) {
            // Read the total number of unique characters from the first line
            totalLines = stoi(line);
        } else if (lineNumber == totalLines + 2) {
            // Store the last line for further processing
            lastLine = line;
        }
        lineNumber++;
    }

    // Process the last line
    for (char ch : lastLine) {
        string word(1, ch);
        frequencies[word]++;
    }

    input.close();

    // Build Huffman tree
    Node* root = buildHuffmanTree(frequencies);

    // Generate Huffman codes
    unordered_map<string, string> codes;
    generateCodes(root, "", codes);

    // Encode input text
    input.open(inputFile);
    getline(input, lastLine);
    input.close();

    string encodedText = encodeWords(line, codes);
    //sort the entries in alphabetical order
    vector<pair<string, int>> sortedEntries(frequencies.begin(), frequencies.end());
    sort(sortedEntries.begin(),sortedEntries.end());

    //terminal output
        if(q5==true){
                // Output number of unique letters
            cout << sortedEntries.size()-1 << endl;
                // Output letters with their respective frequencies and coded words
            for (const auto& entry : sortedEntries) {
                const string& letter = entry.first;
                int frequency = entry.second;
                const string& code = codes[letter];
                cout << letter << " " << frequency << " " << code << endl;
            }
            cout << "Encoded Text: " << encodedText << endl;
                // Output decoded text
            cout << "Decoded Text: " << decodeText(encodedText, root) << endl;
        }

    //write to file
        //Output encoded text to file
    ofstream output(outputFile);
    if (!output) {
        cerr << "Error: Unable to open output file." << endl;
        return;
    }
    output << sortedEntries.size() - 1 << endl;
        for (const auto& entry : sortedEntries) {
        const string& letter = entry.first;
        int frequency = entry.second;
        const string& code = codes[letter];
        output << letter << " " << frequency << " " << code << endl;
    }
    output << encodedText;
    output.close();

}

int huffmanMain() {
    string inputDirectory = "huffman/";
    string outputDirectory = "huffman/";
    string inputFilePrefix = "huffmancoding_";
    string outputFilePrefix = "huffmancoding_";
    string inputFileExtension = "_input.txt";
    string outputFileExtension = "_output.txt";
    bool questionFive=false;

    // Iterate over the input files in the directory
    for (const auto& entry : filesystem::directory_iterator(inputDirectory)) {
        if (entry.is_regular_file()) {
            string inputFilePath = entry.path().string();
            if (inputFilePath.find(inputFilePrefix) != string::npos &&
                inputFilePath.find(inputFileExtension) != string::npos) {
                string fileNumber = inputFilePath.substr(
                    inputFilePath.find(inputFilePrefix) + inputFilePrefix.length(),
                    inputFilePath.find(inputFileExtension) - (inputFilePath.find(inputFilePrefix) + inputFilePrefix.length()));
                string outputFileName = outputFilePrefix + fileNumber + outputFileExtension;
                string outputFilePath = outputDirectory + outputFileName;
                if(inputFilePath == "huffman/huffmancoding_3_input.txt"){
                    questionFive=true;
                }else{
                    questionFive=false;
                }
                huffmanEncoding(inputFilePath, outputFilePath,questionFive);
            }
        }
    }

    return 0;
}
