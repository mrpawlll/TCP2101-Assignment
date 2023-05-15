#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

#include "questions/q2.h"
#include "questions/q1.h"


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
    cout << "3. Quit" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << endl;
    return choice;
}

int main() {
    welcome();
    int choice = menu();
    // Perform actions based on user's choice
    while (choice != 3) {
        switch (choice) {
            case 1:
                initGenerateRandomGraph();
                break;
            case 2:
                initKruskal();
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
