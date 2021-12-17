#ifndef NODE_HPP
#define NODE_HPP

// node struct for storing information of each "cell" in the maze
struct Node {
    // bit flag for storing if a wall exists
    // from leftmost to rightmost bit,
    // top, right, bottom, left
    int walls = (1 << 4) - 1;

    // methods for checking if a wall exists so you don't have to 
    // do bitwise magic everytime
    bool check_top() { return walls & (1 << 3); };
    bool check_right() { return walls & (1 << 2); };
    bool check_bottom() { return walls & (1 << 1); };
    bool check_left() { return walls & 1; };

    // methods to carve out walls
    void carve_top(Node &other);
    void carve_right(Node &other);
    void carve_bottom(Node &other);
    void carve_left(Node &other);
};

#endif
