#include "../include/node.hpp"
using namespace std;

// toggles i-th bit from the right
void toggle_bit(int &target, int i);

// method to destroy top wall
void Node::carve_top(Node &other) {
    // destroys top wall and the bottom wall of node above it

    toggle_bit(walls, 4);
    toggle_bit(other.walls, 2);
}   

// method to destroy right wall
void Node::carve_right(Node &other) {
    // destorys right wall and left wall of node to the right

    toggle_bit(walls, 3);
    toggle_bit(other.walls, 1);
}

// method to destroy bottom wall
void Node::carve_bottom(Node &other) {
    // destorys bottom wall and top wall of node below

    toggle_bit(walls, 2);
    toggle_bit(other.walls, 4);
}

// method to destroy left wall
void Node::carve_left(Node &other) {
    // destorys left wall and right wall of node to the left

    toggle_bit(walls, 1);
    toggle_bit(other.walls, 3);
}

void toggle_bit(int &target, int i) {
    // select the i-th bit
    int mask = 1; mask <<= (i-1);

    // xor with mask
    target ^= mask;
}
