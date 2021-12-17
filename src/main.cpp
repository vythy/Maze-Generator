#include <iostream>
#include <vector>
#include "../include/maze.hpp"
using namespace std;

int getInt(string prompt);

int main() {
    cout << "\nWelcome to Maze generator!\n";

    // Main program loop
    while (true) {
        cout << "\nGenerate a new maze? (y/n): ";
        char choice; cin >> choice;

        if (choice != 'y') break;

        int height = getInt("\nHow many units tall would you like the maze to be?: ");
        int width = getInt("How units wide would you like the maze to be?: ");
        
        // using anonymous object to create a print and new maze quickly to be discarded
        Maze(height, width).print();
    }

    return 0;
}

int getInt(string prompt) {
    cout << prompt;
    int temp; cin >> temp;
    return temp;
}
