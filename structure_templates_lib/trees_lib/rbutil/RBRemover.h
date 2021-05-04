#ifndef SDIZO_1_RBREMOVER_H
#define SDIZO_1_RBREMOVER_H

#include <trees_lib/node_util/NodeRotator.h>
#include "trees_lib/node_util/KeyFinder.h"
#include "trees_lib/node_util/ConsequentFinder.h"
#include "trees_lib/node_util/ConsequentLiberator.h"
#include "trees_lib/node_util/NodeReplacer.h"
#include "trees_lib/nodes/RBNode.h"
#include "trees_lib/nodes/RBFactory.h"

template <typename T>
class RBRemover
{
public:
    explicit RBRemover(NodePointer<T> root);
    void remove(T key);
    NodePointer<T> obtainRoot();

private:
    void resolveDoubleBlack(RBNodePtr<T>);
    NodePointer<T> root;
};

template<typename T>
RBRemover<T>::RBRemover(NodePointer <T> root) {
    this->root = root;
}

template<typename T>
void RBRemover<T>::remove(T key) {
    auto finder = KeyFinder<T>(root);
    finder.setDesiredKey(key);
    finder.find();
    bool treeContainsThatKey = finder.nodeFound();
    if(treeContainsThatKey) {
        auto nodeToRemove = rbcast(finder.getFound());
        auto parent = rbcast(nodeToRemove->getParent());
        Side nodeToRemoveSide = Side::LEFT;
        if(nodeToRemove == parent->getRight())
            nodeToRemoveSide = Side::RIGHT;
        //przypadek pierwszy: brak lewego syna
        if(nodeToRemove->getLeft()->isNil())
        {
            if(!nodeToRemove->getRight()->isNil())
            {
                auto right = rbcast(nodeToRemove->getRight());
                parent->setSide(right, nodeToRemoveSide);
                right->setParent(parent);
                right->paintBlack();
                auto rootFinder = RootFinder<T>(right);
                root = rootFinder.find();
                return;
            }
        }
        //przypadek drugi: brak prawego syna
        if(nodeToRemove->getRight()->isNil())
        {
            if(!nodeToRemove->getLeft()->isNil())
            {
                auto left = rbcast(nodeToRemove->getLeft());
                parent->setSide(left, nodeToRemoveSide);
                left->setParent(parent);
                left->paintBlack();
                auto rootFinder = RootFinder<T>(left);
                root = rootFinder.find();
                return;
            }
        }
        RBNodePtr<T> doubleBlack;
        bool thereIsDoubleBlack = false;
        //czerwony liść usuwamy bezkarnie
        if(nodeToRemove->getRight()->isNil() && nodeToRemove->getLeft()->isNil())
        {
            if(nodeToRemove->isRed())
            {
                parent->setSide(nodeToRemove->getRight(), nodeToRemoveSide);
                return;
            }
            if(nodeToRemove == root)
            {
                root = RBFactory<T>::makeSentinel();
                return;
            }
            //ale czarny nie do końca:
            //przygotowujemy specjalnego podwójnie czarnego strażnika
            auto customSentinel = RBFactory<T>().createSentinel(parent);
            parent->setSide(customSentinel, nodeToRemoveSide);
            thereIsDoubleBlack = true;
            doubleBlack = rbcast(customSentinel);
        } else
        //przypadek 3: posiada dwóch synów, prawy jest następnikiem:
        if(nodeToRemove->getRight()->getLeft()->isNil())
        {
            auto successor = rbcast(nodeToRemove->getRight());
            thereIsDoubleBlack = successor->isBlack();
            //przemalowanie na kolor węzła usuwanego
            if(nodeToRemove->isRed())
                successor->paintRed();
            else
                successor->paintBlack();
            //zamieniamy usuwany węzeł na następnika
            auto left = nodeToRemove->getLeft();
            successor->setLeft(left);
            left->setParent(successor);
            parent->setSide(successor, nodeToRemoveSide);
            successor->setParent(parent);
            if(thereIsDoubleBlack){
                if(successor->getRight()->isNil())
                {
                    auto customSentinel = RBFactory<T>().createSentinel(successor);
                    successor->setRight(customSentinel);
                }
                doubleBlack = rbcast(successor->getRight());
            }
            root = RootFinder<T>(successor).find();
        } else {
            auto successorFinder = ConsequentFinder<T>(nodeToRemove);
            auto successor = rbcast(successorFinder.find());
            thereIsDoubleBlack = successor->isBlack();
            if(nodeToRemove->isRed())
                successor->paintRed();
            else
                successor->paintBlack();
            if(thereIsDoubleBlack){
                if(successor->getRight()->isNil())
                {
                    auto customSentinel = RBFactory<T>().createSentinel(successor);
                    successor->setRight(customSentinel);
                }
                doubleBlack = rbcast(successor->getRight());
            }
            //uwalniamy successora
            {
                auto liberator = ConsequentLiberator<T>(root);
                liberator.free(successor);
            }
            //zastępujemy usuwany węzeł successorem
            {
                auto replacer = NodeReplacer<T>(nodeToRemove);
                replacer.replaceWithNode(successor);
                root = replacer.obtainRoot();
            }
        }
        //jeżeli następnik był czarny lub usunęliśmy czarny liść
        if(thereIsDoubleBlack)
        {
            resolveDoubleBlack(doubleBlack);
        }
    }
}

template<typename T>
NodePointer<T> RBRemover<T>::obtainRoot() {
    return root;
}

template<typename T>
void RBRemover<T>::resolveDoubleBlack(RBNodePtr<T> doubleBlack) {
    //przygotowanie boilerplate'a
    auto dblack = doubleBlack;
    auto dbparent = rbcast(dblack->getParent());
    Side dbside = Side::LEFT;
    if(dbparent->getRight() == dblack)
        dbside = Side::RIGHT;
    auto dbsibling = rbcast(dbparent->get(!dbside));
    while(!dbparent->isNil()){
        //przypadek 1: brat węzła podwójnie czarnego jest czerwony
        if(dbsibling->isRed())
        {
            dbsibling->paintBlack();
            dbparent->paintRed();
            auto rotator = NodeRotator<T>();
            rotator.rotate(dbparent, dbside);
            root = rotator.obtainRoot();
            //aktualizacja genealogii
            dbsibling = rbcast(dbparent->get(!dbside));
        }
        //przypadek 2: brat jest czarny, posiada dwóch czarnych synów
        if(rbcast(dbsibling->getRight())->isBlack() && rbcast(dbsibling->getLeft())->isBlack())
        {
            dbsibling->paintRed();
            dblack = dbparent;
            if(dblack->isRed())
            {
                dblack->paintBlack();
                break;
            }
            //aktualizacja genealogii
            dbparent = rbcast(dblack->getParent());
            dbside = Side::LEFT;
            if(dbparent->getRight() == dblack)
                dbside = Side::RIGHT;
            dbsibling = rbcast(dbparent->get(!dbside));
        }//przypadek 3: brat węzła jest czarny, jego syn od strony usuwanego jest czerwony, a drugi jest czarny
        else {
            if(rbcast(dbsibling->get(dbside))->isRed() && rbcast(dbsibling->get(!dbside))->isBlack())
            {
                auto rotator = NodeRotator<T>();
                rotator.rotate(dbsibling, !dbside);
                root = rotator.obtainRoot();
                //aktualizacja genealogii
                dbsibling = rbcast(dbparent->get(!dbside));
                //przemalowania
                dbsibling->paintBlack();
                rbcast(dbsibling->get(!dbside))->paintRed();
            } //przypadek 4: syn brata od przeciwnej strony jest czerwony
            //przypadek 3 został sprowadzony do przypadku 4
            auto rotator = NodeRotator<T>();
            rotator.rotate(dbparent, dbside);
            root = rotator.obtainRoot();
            auto grand = rbcast(dbparent->getParent());
            if(dbparent->isRed())
                grand->paintRed();
            else
                grand->paintBlack();
            dbparent->paintBlack();
            auto uncle = rbcast(grand->get(!dbside));
            uncle->paintBlack();
            break;
        }
    }
    rbcast(root)->paintBlack();
}

#endif //SDIZO_1_RBREMOVER_H
