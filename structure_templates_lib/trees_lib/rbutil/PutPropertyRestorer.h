#ifndef SDIZO_1_PUTPROPERTYRESTORER_H
#define SDIZO_1_PUTPROPERTYRESTORER_H

#include "trees_lib/node_util/NodeUtility.h"
#include "trees_lib/node_util/NodeRotator.h"
#include "trees_lib/nodes/RBNode.h"

template <typename T>
class PutPropertyRestorer : public NodeUtility<T>
{
public:
    void restoreFrom(RBNodePtr<T> freshNode);
private:
    void updateGenealogy();

    RBNodePtr<T> startingNode;
    RBNodePtr<T> parent;
    RBNodePtr<T> uncle;
    RBNodePtr<T> grand;
    RBNodePtr<T> root;
    Side parentSide;
    Side startingSide;
};

template<typename T>
void PutPropertyRestorer<T>::restoreFrom(RBNodePtr<T> freshNode) {
    startingNode = freshNode;
    updateGenealogy();
    while(parent->isRed()){
        //stryj jest czerwony
        if(uncle->isRed())
        {
            uncle->paintBlack();
            grand->paintRed();
            parent->paintBlack();
            startingNode = grand;
        } else {
            NodeRotator<T> rotator = NodeRotator<T>();
            if(startingSide != parentSide)
            {
                startingNode = parent;
                rotator.rotate(startingNode, parentSide);
                root = rbcast(rotator.obtainRoot());
                updateGenealogy();
            }
            parent->paintBlack();
            grand->paintRed();
            rotator.rotate(grand, !parentSide);//todo tu leży pies pogrzebany
            root = rbcast(rotator.obtainRoot());
            break;
        }
        //jedziemy w górę
        updateGenealogy();
    }
}

template<typename T>
void PutPropertyRestorer<T>::updateGenealogy() {
    currentNode = startingNode;
    parent = rbcast(startingNode->getParent());
    grand = rbcast(parent->getParent());
    if(parent == grand->getLeft())
        parentSide = Side::LEFT;
    else
        parentSide = Side::RIGHT;
    if(startingNode == parent->getLeft())
        startingSide = Side::LEFT;
    else
        startingSide = Side::RIGHT;
    uncle = rbcast(grand->get(!parentSide));
}

#endif //SDIZO_1_PUTPROPERTYRESTORER_H
