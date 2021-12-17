#ifndef MOVEMENT_VECTOR_HPP
#define MOVEMENT_VECTOR_HPP

// struct to help with tracking the floodfill direction
struct MovementVector {
    // for direction bitflags, 1000 = up, 0100 = right, 0010 = down, 0001 = left
    int x, y, direction;
};

#endif