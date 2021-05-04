#include "Side.h"

Side operator!(Side side)
{
    if(side == Side::LEFT)
        return Side::RIGHT;
    else
        return Side::LEFT;
}