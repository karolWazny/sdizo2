#include "RedBlack.h"

bool RedBlack::isBlack() {
    return color == Color::BLACK;
}

bool RedBlack::isRed() {
    return color == Color::RED;
}

void RedBlack::paintBlack() {
    color = Color::BLACK;
}

void RedBlack::paintRed() {
    color = Color::RED;
}