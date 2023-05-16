#include <random>
#include <chrono>
#include <cstring>

string getVertixName(int index) {
    string uniqueLetters;
    int counter = 0;

    if(index == 0){
        return "A";
    }

    while (index > 0) {
        int remainder = index % 26;  // 26 letters in the alphabet
        char letter = 'A' + remainder;
        uniqueLetters = letter + uniqueLetters;
        index = (index - remainder) / 26;
        counter++;
    }

    // Add additional letters if index exceeds 'Z'
    while (counter > 1) {
        uniqueLetters = uniqueLetters;
        counter--;
    }

    return uniqueLetters;
}


// Function to generate a random integer between min and max (inclusive)
int randInt(int min, int max)
{
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}


void tokenize(std::string const &str, const char *delim, vector<int> &out)
{
    char *token = strtok(const_cast<char *>(str.c_str()), delim);
    while (token != nullptr)
    {
        if (token == "i")
        {
            out.push_back(0);
        }
        else
        {
            out.push_back(atoi(token));
        };

        token = strtok(nullptr, delim);
    }
}