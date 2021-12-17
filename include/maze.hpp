#ifndef MAZE_HPP
#define MAZE_HPP

#include "node.hpp"
#include <vector>

// maze class that serves as a container for the nodes 
class Maze {
    private:
        int height, width;

        // 2D node array to represent the maze and visited array to make sure that a node is only visited once
        std::vector<std::vector<Node>> nodes;
        std::vector<std::vector<bool>> visited;

        //2D char array for outputting the maze
        std::vector<std::vector<char>> out;

    public:
        // constructor that takes in a height and width for the maze
        Maze(int h, int w);

        // main function for the maze generation algo
        void generate();

        // outputting the maze to the terminal
        void print();
};

#endif