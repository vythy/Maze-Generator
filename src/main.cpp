/*
    ASCII Maze Generator by Justin le

    creates cool randomized mazes that you can specify the dimensions of
*/

#include <iostream>
#include <vector>
#include "../include/maze.hpp"
using namespace std;

int getInt(string prompt);
int getChar(string prompt);

int main() {
    cout << "\nWelcome to Maze generator!\n";

    // Main program loop
    while (true) {
        if (getChar("\nGenerate a new maze? (y/n): ") != 'y') break;

        int height = getInt("\nHow many units tall would you like the maze to be?: ");
        int width = getInt("How units wide would you like the maze to be?: ");
        
        // using anonymous object to create a print and new maze quickly to be discarded
        Maze(height, width).print();
    }

    return 0;
}

int getChar(string prompt) {
    cout << prompt;
    char temp; cin >> temp;
    return temp;
}

int getInt(string prompt) {
    cout << prompt;
    int temp; cin >> temp;
    return temp;
}
