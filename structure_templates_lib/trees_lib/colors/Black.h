#ifndef SDIZO_1_BLACK_H
#define SDIZO_1_BLACK_H

#include "Colored.h"

class Black : public Colored{
public:
    bool isBlack() override;
    bool isRed() override;
    void paintBlack() override;
    void paintRed() override;
};


#endif //SDIZO_1_BLACK_H
