#ifndef SDIZO_1_TREESIZER_H
#define SDIZO_1_TREESIZER_H

#include "trees_lib/nodes/Node.h"

template <typename T>
class TreeSizer
{
public:
    int size(NodePointer<T>);
};

template<typename T>
int TreeSizer<T>::size(NodePointer<T> root) {
    if(root->isNil())
        return 0;
    int output = size(root->getLeft());
    output += size(root->getRight());
    output++;
    return output;
}

#endif //SDIZO_1_TREESIZER_H
