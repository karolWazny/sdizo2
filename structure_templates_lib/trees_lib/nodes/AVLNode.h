#ifndef SDIZO_1_AVLNODE_H
#define SDIZO_1_AVLNODE_H

template <typename T>
class AVLNode;

template <typename T>
using AVLNodePtr = std::shared_ptr<AVLNode<T>>;

template <typename T>
class AVLNode : public Node<T>
{
public:
    virtual T getKey() = 0;
    virtual void setParent(NodePointer<T>) = 0;
    virtual NodePointer<T> getParent() = 0;
    virtual void setLeft(NodePointer<T>) = 0;
    virtual NodePointer<T> getLeft() = 0;
    virtual void setRight(NodePointer<T>) = 0;
    virtual NodePointer<T> getRight() = 0;
    virtual bool isNil() = 0;

    virtual char getBalanceFactor() = 0;
    virtual void setBalanceFactor(char factor) = 0;
    void addBalance(Side side);
};

template<typename T>
void AVLNode<T>::addBalance(Side side) {
    auto bf = getBalanceFactor();
    if(side == Side::RIGHT)
        bf++;
    else
        bf--;
    setBalanceFactor(bf);
}

template <typename T>
AVLNodePtr<T> avlcast(NodePointer<T> node) {
    return std::dynamic_pointer_cast<AVLNode<T>>(node);
}

#endif //SDIZO_1_AVLNODE_H
