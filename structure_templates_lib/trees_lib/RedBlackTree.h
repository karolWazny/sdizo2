#ifndef SDIZO_1_REDBLACKTREE_H
#define SDIZO_1_REDBLACKTREE_H

#include "trees_lib/nodes/Node.h"
#include "trees_lib/node_util/KeyFinder.h"
#include "trees_lib/nodes/RBFactory.h"
#include "trees_lib/rbutil/RBPutter.h"
#include "trees_lib/rbutil/RBRemover.h"
#include "trees_lib/node_util/TreePrinter.h"


template <typename T>
class RedBlackTree
{
public:
    RedBlackTree();
    void put(T key);
    bool contains(T key);
    void remove(T key);
    string toString();
    string getRepresentation();
    bool isEmpty();
private:
    NodePointer<T> root;
};

template <typename T>
RedBlackTree<T>::RedBlackTree() {
    root = SimpleFactory<T>::makeSentinel();
}

template<typename T>
void RedBlackTree<T>::put(T key) {
    auto putter = RBPutter<T>(root);
    putter.put(key);
    root = putter.obtainRoot();
#if DEBUG
    rbcast(root)->checkAmountOfBlackToLeaves();
#endif
}

template<typename T>
bool RedBlackTree<T>::contains(T key) {
    auto finder = KeyFinder<T>(root);
    finder.setDesiredKey(key);
    finder.find();
    return finder.nodeFound();
}

template<typename T>
void RedBlackTree<T>::remove(T key) {
    auto remover = RBRemover<T>(root);
    remover.remove(key);
    root = remover.obtainRoot();
#if DEBUG
    rbcast(root)->checkAmountOfBlackToLeaves();//todo przywrócić ten warunek
#endif
}

template<typename T>
string RedBlackTree<T>::toString() {
    return TreePrinter<T>().toString(root);
}

template<typename T>
string RedBlackTree<T>::getRepresentation() {
    return TreePrinter<T>().rbMonospaceRepresentation(root);
}

template<typename T>
bool RedBlackTree<T>::isEmpty() {
    return root->isNil();
}

#endif //SDIZO_1_REDBLACKTREE_H
