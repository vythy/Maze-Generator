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
bool has_wall(MovementVector &current, string direction);
void set_adj_walls(vector<vector<Node>> &in, vector<vector<char>> &out, int i, int j);
void convert(vector<vector<Node>> &in, vector<vector<char>> &out, int height, int width);
void carve(MovementVector &prev, MovementVector &next, vector<vector<Node>> &nodes);
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

            carve(top, choose, nodes);

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

// simplifies bitflag check for walls
bool has_wall(MovementVector &current, string direction) {
    int bit_check = 1;
    if (direction == "top") bit_check <<= 3;
    else if (direction == "right") bit_check <<= 2;
    else if (direction == "bottom") bit_check <<= 1;

    return (current.direction & bit_check);
}


// chooses the right wall to carve from coords direction bitflag
void carve(MovementVector &prev, MovementVector &next, vector<vector<Node>> &nodes) {
    // this is kinda messy ngl
    // checks direction explored to decide how to break down walls
    if ( has_wall(next, "left") ) {
        nodes[prev.y][prev.x].carve_left( nodes[next.y][next.x] );
    } else if ( has_wall(next, "bottom") ) {
        nodes[prev.y][prev.x].carve_bottom( nodes[next.y][next.x] );
    } else if ( has_wall(next, "right") ) {
        nodes[prev.y][prev.x].carve_right( nodes[next.y][next.x] );
    } else if ( has_wall(next, "top") ) {
        nodes[prev.y][prev.x].carve_top( nodes[next.y][next.x] );
    }
}

// helper function to conver the maze data structure into an ascii grid
void convert(vector<vector<Node>> &in, vector<vector<char>> &out, int height, int width) {
    // Go through every single node and create its individual grid for the output matrix
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            set_adj_walls(in, out, i, j);
        }
    }
}

// each node occupies a 3x3 plus sign in the output matrix
// therefore center of each 3x3 is defined as the point 2i+1, 2j+1
// add 1 in each direction and decide whether a wall should be placed
// sets walls in the plus sign pattern
void set_adj_walls(vector<vector<Node>> &in, vector<vector<char>> &out, int i, int j) {
    out[i*2+1][j*2] = ( in[i][j].check_left() ) ? '#' : ' ';
    out[i*2+1][j*2+2] = ( in[i][j].check_right() ) ? '#' : ' ';
    out[i*2][j*2+1] = ( in[i][j].check_top() ) ? '#' : ' ';
    out[i*2+2][j*2+1] = ( in[i][j].check_bottom() ) ? '#' : ' ';
    out[i*2+1][j*2+1] = ' ';
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
            #ifdef _WIN32
            Sleep(1);
            #else 
            usleep(1000);
            #endif
        }
        cout << "\n";
    }

    cout << "\n\n";
}
