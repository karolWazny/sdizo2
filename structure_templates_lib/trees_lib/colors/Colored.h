#ifndef SDIZO_1_COLORED_H
#define SDIZO_1_COLORED_H

class Colored
{
public:
    virtual bool isBlack() = 0;
    virtual bool isRed() = 0;
    virtual void paintBlack() = 0;
    virtual void paintRed() = 0;
};

#endif //SDIZO_1_COLORED_H
