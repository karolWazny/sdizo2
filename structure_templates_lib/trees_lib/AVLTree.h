#ifndef SDIZO_1_AVLTREE_H
#define SDIZO_1_AVLTREE_H

#include "trees_lib/nodes/Node.h"
#include "trees_lib/node_util/KeyFinder.h"
#include "trees_lib/AVLPutter.h"
#include "trees_lib/rbutil/RBRemover.h"
#include "trees_lib/node_util/TreePrinter.h"
#include "AVLRemover.h"

template <typename T>
class AVLTree {
public:
    AVLTree();
    void put(T key);
    bool containsKey(T key);
    void removeKey(T key);
    string toString();
    string getRepresentation();
    bool isEmpty();
private:
    NodePointer<T> root;
};

template<typename T>
AVLTree<T>::AVLTree() {
    root = SimpleFactory<T>::makeSentinel();
}

template<typename T>
void AVLTree<T>::put(T key) {
    auto putter = AVLPutter<T>(root);
    putter.put(key);
    root = putter.obtainRoot();
}

template<typename T>
bool AVLTree<T>::containsKey(T key) {
    auto finder = KeyFinder<T>(root);
    finder.setDesiredKey(key);
    finder.find();
    return finder.nodeFound();
}

template<typename T>
void AVLTree<T>::removeKey(T key) {
    auto remover = AVLRemover<T>(root);
    remover.remove(key);
    root = remover.obtainRoot();
}

template<typename T>
string AVLTree<T>::toString() {
    return TreePrinter<T>().toString(root);
}

template<typename T>
string AVLTree<T>::getRepresentation() {
    return TreePrinter<T>().rbMonospaceRepresentation(root);
}

template<typename T>
bool AVLTree<T>::isEmpty() {
    return root->isNil();
}

#endif //SDIZO_1_AVLTREE_H
