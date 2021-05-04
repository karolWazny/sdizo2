#ifndef SDIZO_1_SIDE_H
#define SDIZO_1_SIDE_H

enum class Side : char
{
    RIGHT,
    LEFT
};

Side operator!(Side side);

#endif //SDIZO_1_SIDE_H
