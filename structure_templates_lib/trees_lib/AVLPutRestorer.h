#ifndef SDIZO_1_AVLPUTRESTORER_H
#define SDIZO_1_AVLPUTRESTORER_H

#include "trees_lib/node_util/NodeUtility.h"
#include "trees_lib/nodes/AVLNode.h"
#include "trees_lib/node_util/NodeRotator.h"

template <typename T>
class AVLPutRestorer : public NodeUtility<T>
{
public:
    void restoreFrom(AVLNodePtr<T> freshNode);
private:
    void performRotations();

    Side currentSide;
    Side parentSide;
    AVLNodePtr<T> currentParent;
    AVLNodePtr<T> currentGrand;
    AVLNodePtr<T> current;
};

template<typename T>
void AVLPutRestorer<T>::restoreFrom(AVLNodePtr<T> freshNode) {
    if(freshNode->getParent()->isNil())
    {
        currentNode = freshNode;
        return;
    }
    current = freshNode;
    currentParent = avlcast(current->getParent());

    //jeżeli ojciec dodanego węzła był niezrównoważony o jeden, to teraz
    //na pewno jest zrównoważony
    if(currentParent->getBalanceFactor())
    {
        currentParent->setBalanceFactor(0);
        return;
    }
    currentGrand = avlcast(currentParent->getParent());
    //pozyskanie wiedzy, z której strony
    if(currentParent->getRight() == current)
        currentSide = Side::RIGHT;
    else
        currentSide = Side::LEFT;

    if(currentGrand->getRight() == currentParent)
        parentSide = Side::RIGHT;
    else
        parentSide = Side::LEFT;

    currentParent->addBalance(currentSide);
    while(!currentParent->isNil())
    {
        currentGrand->addBalance(parentSide);
        if(currentGrand->getBalanceFactor() == 2 || currentGrand->getBalanceFactor() == -2)
        {
            performRotations();
            return;
        }
        current = currentParent;
        currentParent = currentGrand;
        currentGrand = avlcast(currentGrand->getParent());
        if(currentParent->getRight() == current)
            currentSide = Side::RIGHT;
        else
            currentSide = Side::LEFT;

        if(currentGrand->getRight() == currentParent)
            parentSide = Side::RIGHT;
        else
            parentSide = Side::LEFT;
    }
}

template<typename T>
void AVLPutRestorer<T>::performRotations() {
    char a, b, c;
    a = currentGrand->getBalanceFactor();
    b = currentParent->getBalanceFactor();
    //przypadek: koniecznosc rotacji podwojnej
    if(a * b < 0) {
        c = current->getBalanceFactor();
        char bTimesC = b * c;
        if(bTimesC < 0)
            a /= -2;
        else {
            a = 0;
            if(bTimesC > 0)
                b = -b;
            else
                b = 0;
        }
        c = 0;
        auto rotator = NodeRotator<T>();
        rotator.rotate(currentParent, parentSide);
        currentNode = RootFinder<T>(currentParent).find();
        rotator.rotate(currentGrand, !parentSide);
        currentNode = RootFinder<T>(currentGrand).find();
        current->setBalanceFactor(0);
        currentParent->setBalanceFactor(b);
        currentGrand->setBalanceFactor(a);
    } else {//przypadek: koniecznosc rotacji pojedynczej
        if(!b)
        {
            a /= 2;
            b = -((int)a);
        } else {
            a = 0;
            b = 0;
        }
        auto rotator = NodeRotator<T>();
        rotator.rotate(currentGrand, !parentSide);
        currentNode = RootFinder<T>(currentParent).find();
        currentParent->setBalanceFactor(b);
        currentGrand->setBalanceFactor(a);
    }

}

#endif //SDIZO_1_AVLPUTRESTORER_H
