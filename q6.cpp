#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct LetterFrequency{
    char letter;
    int frequency;
};

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

vector<string> generateRandomWordVector(){  
    int numOfWords = 0;
    vector<string> words;

    cout << "Enter number of words to be generated" << endl;
    cin >> numOfWords;

    for (int i = 0; i < numOfWords; i++)
    {
        string Temp = generateRandomWord(9);
        words.push_back(Temp);
    }
    return words;
}

vector<LetterFrequency> countDistinctLetters(const vector<string>& words) {
    unordered_map<char, int> frequencyMap; //unordered map for automatic
                                           //handling of unique letters
                                           //from different words collectively

    for (const string& word : words) { // itterate words vector
        for (char letter : word) { //itterate letters in string word

            frequencyMap[letter]++; // adds letter to the map, stacking the letter's frequncies
                                    // for each letter found in words vector
                                    // snce it is unordered map if a new letter is inserted
                                    // it will create a new key pair in the map and increment its calue by 1
                                    // if letter is already present within the unordered map then it automatically
                                    // increments that key's value by 1

        }
    }

    vector<LetterFrequency> distinctLetters;
    for (const auto& pair : frequencyMap) { // pair = char as the key and int as the value
        LetterFrequency lf;
        lf.letter = pair.first; // 1st pair is the key which is the letter
        lf.frequency = pair.second; // 2nd pair is value which is frequency of the letter
        distinctLetters.push_back(lf);
    }

    sort(distinctLetters.begin(), distinctLetters.end(), 
         [](const LetterFrequency& a, const LetterFrequency& b) { // sorts distinct letters vector based
                                                                  // on alphabetical order
             return a.letter < b.letter;
         });

    return distinctLetters;
}

void storeDataInFile(const vector<LetterFrequency>& distinctLetters, const vector<string>& words) {
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        // Store number of distinct letters
        int numDistinctLetters = distinctLetters.size();
        outputFile << numDistinctLetters << endl;

        // Store distinct letters
        for (const auto& lf : distinctLetters) {
            outputFile << lf.letter << " ";
            outputFile << endl;
        }
    
        // Store generated words
        for (const auto& word : words) {
            outputFile << word << endl;
        }

        outputFile.close();
        cout << "Data stored in output.txt file." << endl;
    } else {
        cout << "Unable to open the file for writing." << endl;
    }
}


int main()
{
vector<string> words = generateRandomWordVector();
    vector<LetterFrequency> distinctLetters = countDistinctLetters(words);
    storeDataInFile(distinctLetters, words);

}