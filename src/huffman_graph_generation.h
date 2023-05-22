#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>

using namespace std;

string generateRandomWord(int Wordlength)
{
    string word = "";
    for (int i = 0; i < Wordlength; i++) // amount of iteration depends on 'WordLength'
    {
        char letter = 'A' + rand() % 26; // this line uses asccii code of letter A and
                                         // produces random letters ranging from A to Z
                                         // 26 is essentially the range of the alphabet

        word += letter; // this will add every letter to the string word
    }

    return word; // returns the random word
}

vector<string> generateRandomWordVector(int numOfWords)
{
    vector<string> words;

    for (int i = 0; i < numOfWords; i++)
    {
        string temp = generateRandomWord(5);
        words.push_back(temp);
    }
    return words;
}

vector<LetterFrequency> countDistinctLetters(const vector<string> &words)
{
    unordered_map<char, int> frequencyMap; // unordered map for automatic
                                           // handling of unique letters
                                           // from different words collectively

    for (const string &word : words)
    { // itterate word strings from words vector
        for (char letter : word)
        { // itterate letters from string word

            frequencyMap[letter]++; // adds letter to the map, stacking the letter's frequncies.
                                    // since it is unordered map if a new letter is inserted
                                    // it will create a new key pair in the map and increment its value by 1
                                    // if letter is already present within the unordered map then it automatically
                                    // increments that key's value by 1
        }
    }

    vector<LetterFrequency> distinctLetters;
    for (const auto &pair : frequencyMap)
    { // pair = char as the key and int as the value
        LetterFrequency lf;
        lf.letter = pair.first;     // 1st pair is the key which is the letter
        lf.frequency = pair.second; // 2nd pair is value which is frequency of the letter
        distinctLetters.push_back(lf);
    }

    sort(distinctLetters.begin(), distinctLetters.end(),
         [](const LetterFrequency &a, const LetterFrequency &b) { // sorts distinct letters vector based
                                                                  // on alphabetical order
             return a.letter < b.letter;
         });

    return distinctLetters;
}

void storeDataInFile(ofstream &file, const vector<LetterFrequency> &distinctLetters, const vector<string> &words)
{

    // Store number of distinct letters
    int numDistinctLetters = words.size();
    file << numDistinctLetters << endl;

    // Store distinct letters
    for (const auto &lf : distinctLetters)
    {
        file << lf.letter << " " << lf.frequency;
        file << endl;
    }

    // Store generated words
    for (const auto &word : words)
    {
        file << word << endl;
    }
}

int Huffman_GraphGenerator()
{
    // Generate 5 random input files with various sizes
    for (int n : {10, 100}) // 1000, 10000, 100000
    {
        fs::create_directory("huffman");

        string filename = "huffman/huffmancoding_" + std::to_string(n) + "_input.txt";
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file " << filename << endl;
            return 1;
        }

        vector<string> words = generateRandomWordVector(n);
        vector<LetterFrequency> distinctLetters = countDistinctLetters(words);


        storeDataInFile(file, distinctLetters, words);

        file.close();

        cout << "File " << filename << " created successfully." << endl;
    }
    return 0;
}