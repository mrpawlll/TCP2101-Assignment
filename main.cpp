#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>

using namespace std;

namespace fs = std::filesystem;

#include "src/utils.h"
#include "src/entities.h"

#include "src/kruskal.h"
#include "src/kruskal_graph_generation.h"

#include "src/huffman_graph_generation.h"
#include "src/huffmancoding.h"


// Function to display the welcome message
void welcome() {
    cout << "Algorithm & Desgin Assigment" << endl;
    cout << endl;
}

// Function to display the menu options and get user input
int menu() {
    int choice;
    cout << "Please choose an option:" << endl;
    cout << "1. Generate Kruskal Input Files" << endl;
    cout << "2. Process Kruskal Files " << endl;
    cout << "3. Generate Huffman Input Files " << endl;
    cout << "4. Process Huffman Files" << endl;
    cout << "5. Quit" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << endl;
    return choice;
}

int main()
{
    welcome();
    int choice = menu();
    // Perform actions based on user's choice
    while (choice != 5)
    {
        switch (choice)
        {
        case 1:
            initGenerateRandomGraph();
            break;
        case 2:
            initKruskal();
            break;
        case 3:
            Huffman_GraphGenerator();
            break;
        case 4:
           huffmanMain();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        choice = menu();
    }
    cout << "Thank you for using the minimum spanning tree problem solver!" << endl;
    return 0;
}
