#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>

#include "../include/maze.hpp"
#include "../include/node.hpp"
#include "../include/movement_vector.hpp"

#ifdef _WIN32
#include <Windows.h>
#else 
#include <unistd.h>
#endif

using namespace std;

// helper function declarations
bool check(MovementVector &current, int height, int width, vector<vector<bool>> &visited);
void convert(vector<vector<Node>> &in, vector<vector<char>> &out, int height, int width);
vector<MovementVector> floodfill(MovementVector current, int height, int width, vector<vector<bool>> &visited);

// legal movement directions for floodfill/neighbor search
// left, down, right, up
const int hdirections[4] = {-1, 0, 1, 0};
const int vdirections[4] = {0, 1, 0, -1};

// maze constructor
Maze::Maze(int h, int w) {
    height = h;
    width = w;

    // resizing 2D vectors to be correct width and height
    // output vector must have dimensions set as 2x+1 due to walls
    nodes.resize(h, vector<Node>(w));
    visited.resize(h, vector<bool>(w));
    out.resize(h*2+1, vector<char>(w*2+1, '#'));

    generate();
}

// maze generation algorithm which is essentially just a DFS backtracker
// proof that it generates a path to the end is as follows:
// for every node i in maze m, i must have a path to at LEAST one of its adjacent nodes, j. 
// therefore there must exist one ST (Spanning Tree) from any node to any other node.

void Maze::generate() {
    srand(time(0));

    // stack that keeps track of the next node to search neighbors
    stack<MovementVector> stck;
    stck.push({0, 0, 0});

    // break entrance and exit walls
    nodes[0][0].walls ^= (1 << 3);
    nodes[height-1][width-1].walls ^= (1 << 1);

    // keep going as long as there are nodes to back track to
    while (stck.size()) {
        MovementVector top = stck.top();
        stck.pop();

        while (true) {
            vector<MovementVector> candidates = floodfill(top, height, width, visited);

            // start backtrack if current node has no explorable neighbors
            if (candidates.empty()) break;

            // choose a random neighbor to explore
            int chooseIndex = rand() % candidates.size();
            MovementVector choose = candidates[chooseIndex];

            // add the new node to backtrack stack
            stck.push(choose);

            // this is kinda messy ngl
            // checks direction explored to decide how to break down walls
            if (choose.direction & (1 << 0)) {
                nodes[top.y][top.x].carve_left( nodes[choose.y][choose.x] );
            } else if (choose.direction & (1 << 1)) {
                nodes[top.y][top.x].carve_bottom( nodes[choose.y][choose.x] );
            } else if (choose.direction & (1 << 2)) {
                nodes[top.y][top.x].carve_right( nodes[choose.y][choose.x] );
            } else if (choose.direction & (1 << 3)) {
                nodes[top.y][top.x].carve_top( nodes[choose.y][choose.x] );
            }

            // make most recently visited node the new one being considered
            top = choose;
            visited[choose.y][choose.x] = 1;
        }
    }

    convert(nodes, out, height, width);
}

// helper function used to verify that a node is valid
bool check(MovementVector &current, int height, int width, vector<vector<bool>> &visited) {
    return (current.x >= 0 && current.y >= 0 && current.x < width && current.y < height) 
            && (!visited[current.y][current.x]);
}

// helper function to conver the maze data structure into an ascii grid
void convert(vector<vector<Node>> &in, vector<vector<char>> &out, int height, int width) {
    // each node occupies a 3x3 plus sign in the output matrix
    // therefore center of each 3x3 is defined as the point 2i+1, 2j+1
    // add 1 in each direction and decide whether a wall should be placed
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            out[i*2+1][j*2] = ( in[i][j].check_left() ) ? '#' : ' ';
            out[i*2+1][j*2+2] = ( in[i][j].check_right() ) ? '#' : ' ';
            out[i*2][j*2+1] = ( in[i][j].check_top() ) ? '#' : ' ';
            out[i*2+2][j*2+1] = ( in[i][j].check_bottom() ) ? '#' : ' ';
            out[i*2+1][j*2+1] = ' ';
        }
    }
}

// helper function used to generate the potential neighbors to explore
vector<MovementVector> floodfill(MovementVector current, int height, int width, vector<vector<bool>> &visited) {
    vector<MovementVector> ret;

    // loop through all directions
    for (int i = 3; i >= 0; --i) {
        MovementVector temp = current;
        int flag = 1;

        // set direction flag
        flag <<= i;
        temp.direction = flag;

        temp.x += hdirections[i]; temp.y += vdirections[i];

        if (check(temp, height, width, visited)) {
            ret.push_back(temp);
        }
    }

    return ret;
}

void Maze::print() {
    cout << "\n\n";
    // looping through char matrix to output
    // uses a small sleep to make it look like its animating
    for (int i = 0; i < height*2+1; ++i) {
        for (int j = 0; j < width*2+1; ++j) {
            cout << out[i][j];
            Sleep(1);
        }
        cout << "\n";
    }

    cout << "\n\n";
}