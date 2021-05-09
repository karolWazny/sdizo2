#ifndef SDIZO2_LISTITERATOR_H
#define SDIZO2_LISTITERATOR_H

#include "INextable.h"

template <typename T>
class LinkedList;

template <typename T>
class ListIterator {
public:
    ListIterator(LinkedList<T>* owner,
                 std::shared_ptr<INextable<T>> first) : current{first},
                 owningList{owner} {};
    bool hasNext();
    T& next();
    void remove();
private:
    std::shared_ptr<INextable<T>> current;
    LinkedList<T>* owningList;
};

template<typename T>
bool ListIterator<T>::hasNext() {
    return current->hasNext();
}

template<typename T>
T &ListIterator<T>::next() {
    current = current->getNext();
    return current->getContent();
}

template<typename T>
void ListIterator<T>::remove() {
    bool isLast = !current->hasnext();
    if(isLast) {
        owningList->lasteIndex = current->getPrevious();
    }
    current->remove();
}

#endif //SDIZO2_LISTITERATOR_H
