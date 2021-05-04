#ifndef SDIZO_1_TREEPRINTER_H
#define SDIZO_1_TREEPRINTER_H

#include <string>
#include <vector>
#include "trees_lib/nodes/RBNode.h"
#include "trees_lib/node_util/TreeSizer.h"

using string = std::string;

template<typename T>
class TreePrinter
{
public:
    string toString(NodePointer<T> root);
    string rbMonospaceRepresentation(NodePointer <T>);
private:
    void rbMonospaceRepresentationRecursive(std::vector<std::string>&, int begin, NodePointer<T>);
    string stringarize(NodePointer<T> root);
    string rbNodeString(NodePointer<T>);
};

template<typename T>
string TreePrinter<T>::toString(NodePointer <T> root) {
    string output = "[";
    output += stringarize(root);
    output += "]";
    return output;
}

template<typename T>
string TreePrinter<T>::stringarize(NodePointer <T> root) {
    if(root->isNil())
        return "";
    string output;
    output += stringarize(root->getLeft());
    if(!output.empty())
        output += ", ";
    output += std::to_string(root->getKey());
    string buffer = stringarize(root->getRight());
    if(!buffer.empty())
        output += ", ";
    output += buffer;
    return output;
}

template<typename T>
string TreePrinter<T>::rbMonospaceRepresentation(NodePointer<T> root) {
    int size = TreeSizer<T>().size(root);
    if(size == 0)
        return "[]";
    std::vector<std::string> partialRepresentations(size);
    rbMonospaceRepresentationRecursive(partialRepresentations, 0, root);
    std::string output;
    for(int i = 0; i < size; i++)
    {
        output += "\n";
        std::string buffer = partialRepresentations[i];
        output += buffer;
    }
    return output;
}

template<typename T>
string TreePrinter<T>::rbNodeString(NodePointer<T> node) {
    string out;
    out += (rbcast(node)->isRed() ? 'R' : 'B');
    out += std::to_string(node->getKey());
    return out;
}

template<typename T>
void TreePrinter<T>::rbMonospaceRepresentationRecursive(std::vector<std::string> &partials,
        int begin, NodePointer<T> subtreeRoot) {
    if(subtreeRoot->isNil())
        return;
    auto left = subtreeRoot->getLeft();
    auto leftSize = TreeSizer<T>().size(left);
    auto leftRightSize = TreeSizer<T>().size(left->getRight());

    auto right = subtreeRoot->getRight();
    auto rightSize = TreeSizer<T>().size(right);
    auto rightRightSize = TreeSizer<T>().size(right->getRight());
    int cornersCount = 0;
    for(int i = 0; i < rightRightSize; i++)
    {
        partials[begin + i] += " ";
    }
    if(!right->isNil())
    {
        partials[begin + rightRightSize] += (char)218;//lewy górny narożnik
        cornersCount++;
    }
    for(int i = rightRightSize + cornersCount; i < rightSize; i++)
    {
        partials[begin + i] += (char)179;//pionowa kreska
    }
    partials[begin + rightSize] += subtreeRoot->toString();
    for(int i = 0; i < leftRightSize; i++)
    {
        partials[begin + rightSize + 1 + i] += (char)179;//pionowa kreska
    }
    cornersCount = 0;
    if(!left->isNil())
    {
        partials[begin + rightSize + 1 + leftRightSize] += (char)192;//lewy dolny narożnik
        cornersCount++;
    }
    for(int i = leftRightSize + cornersCount + 1; i <= leftSize; i++)
    {
        partials[begin + rightSize + i] += " ";
    }
    rbMonospaceRepresentationRecursive(partials, begin, right);
    rbMonospaceRepresentationRecursive(partials, begin + rightSize + 1, left);
}

#endif //SDIZO_1_TREEPRINTER_H
