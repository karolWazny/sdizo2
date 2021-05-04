#ifndef SDIZO_1_AVLREMOVER_H
#define SDIZO_1_AVLREMOVER_H

#include "trees_lib/nodes/AVLNode.h"
#include "trees_lib/node_util/NodeUtility.h"
#include "trees_lib/node_util/KeyFinder.h"

template <typename T>
class AVLRemover : public NodeUtility<T>
{
public:
    explicit AVLRemover(NodePointer<T> root);
    void remove(T key);
private:
    bool findNode(T key);

    void restoreFrom(AVLNodePtr<T> startingNode);
    AVLNodePtr<T> nodeToRemove;
    AVLNodePtr<T> nodeToRemoveParent;
    Side nodeToRemoveSide;
};

template<typename T>
void AVLRemover<T>::remove(T key) {
    bool nodeFound = findNode(key);
    if(nodeFound)
    {
        nodeToRemoveParent = avlcast(nodeToRemove->getParent());
        if(!nodeToRemoveParent)
        {
            nodeToRemove->setParent(AVLSentinel<T>::getInstance());
            nodeToRemoveParent = avlcast(nodeToRemove->getParent());
        }
        nodeToRemoveSide = Side::LEFT;
        if(nodeToRemoveParent->getRight() == nodeToRemove)
            nodeToRemoveSide = Side::RIGHT;
        //przypadek:tylko prawy syn
        if(!nodeToRemove->getRight()->isNil() && nodeToRemove->getLeft()->isNil())
        {
            auto child = nodeToRemove->getRight();
            child->setParent(nodeToRemoveParent);
            nodeToRemoveParent->setSide(child, nodeToRemoveSide);
            nodeToRemoveParent->addBalance(!nodeToRemoveSide);
            currentNode = RootFinder<T>(child).find();
            restoreFrom(nodeToRemoveParent);
            return;
        }//przypadek symetryczny: tylko lewy syn
        else if(nodeToRemove->getRight()->isNil() && !nodeToRemove->getLeft()->isNil())
        {
            auto child = nodeToRemove->getLeft();
            child->setParent(nodeToRemoveParent);
            nodeToRemoveParent->setSide(child, nodeToRemoveSide);
            nodeToRemoveParent->addBalance(!nodeToRemoveSide);
            currentNode = RootFinder<T>(child).find();
            restoreFrom(nodeToRemoveParent);
            return;
        }//przypadek: usuwamy węzeł bezdzietny
        else if(nodeToRemove->getRight()->isNil() && nodeToRemove->getLeft()->isNil())
        {
            currentNode = nodeToRemoveParent;
            nodeToRemoveParent->setSide(nullptr, nodeToRemoveSide);
            restoreFrom(nodeToRemoveParent);
            return;
        }//przypadek: oba syny, prawy syn jest następnikiem
        else if(nodeToRemove->getRight()->getLeft()->isNil())
        {
            auto child = avlcast(nodeToRemove->getRight());
            //podmianka
            child->setParent(nodeToRemoveParent);
            nodeToRemoveParent->setSide(child, nodeToRemoveSide);

            auto left = nodeToRemove->getLeft();
            left->setParent(child);
            child->setLeft(left);

            child->setBalanceFactor(nodeToRemove->getBalanceFactor() - 1);
            currentNode = RootFinder<T>(child).find();
            restoreFrom(child);
            return;
        }//przypadek każdy inny: oba syny, prawy to nie następnik
        else {
            //znalezienie i uwolnienie następnika
            auto successorFinder = ConsequentFinder<T>(nodeToRemove);
            auto successor = avlcast(successorFinder.find());
            auto sParent = avlcast(successor->getParent());
            auto liberator = ConsequentLiberator<T>(currentNode);//w tym momencie w currentnode jest root
            liberator.free(successor);
            //podmianka
            successor->setBalanceFactor(nodeToRemove->getBalanceFactor());
            auto replacer = NodeReplacer<T>(nodeToRemove);
            replacer.replaceWithNode(successor);
            sParent->addBalance(Side::RIGHT);//gałąź z lewej zrobiła się lżejsza
            currentNode = RootFinder<T>(successor).find();
            restoreFrom(sParent);
            return;
        }
    }
}

template<typename T>
AVLRemover<T>::AVLRemover(NodePointer<T> root) {
    currentNode = root;
}

template<typename T>
bool AVLRemover<T>::findNode(T key) {
    auto finder = KeyFinder<T>(currentNode);
    finder.setDesiredKey(key);
    nodeToRemove = avlcast(finder.find());
    return finder.nodeFound();
}

template<typename T>
void AVLRemover<T>::restoreFrom(AVLNodePtr<T> startingNode) {

}

#endif //SDIZO_1_AVLREMOVER_H
