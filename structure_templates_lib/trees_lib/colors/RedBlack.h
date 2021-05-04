#ifndef SDIZO_1_REDBLACK_H
#define SDIZO_1_REDBLACK_H

#include "trees_lib/colors/Colored.h"

enum class Color : char
{
    RED,
    BLACK
};

class RedBlack : public Colored
{
public:
    bool isBlack() override;
    bool isRed() override;
    void paintBlack() override;
    void paintRed() override;
private:
    Color color;
};

#endif //SDIZO_1_REDBLACK_H
