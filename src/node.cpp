#include "../include/node.hpp"
using namespace std;

// method to destroy top wall
void Node::carve_top(Node &other) {
    // destroys top wall and the bottom wall of node above it
    walls ^= (1 << 3);
    other.walls ^= (1 << 1);
}   

// method to destroy right wall
void Node::carve_right(Node &other) {
    // destorys right wall and left wall of node to the right
    walls ^= (1 << 2);
    other.walls ^= 1;
}

// method to destroy bottom wall
void Node::carve_bottom(Node &other) {
    // destorys bottom wall and top wall of node below
    walls ^= (1 << 1);
    other.walls ^= (1 << 3);
}

// method to destroy left wall
void Node::carve_left(Node &other) {
    // destorys left wall and right wall of node to the left
    walls ^= 1;
    other.walls ^= (1 << 2);
}