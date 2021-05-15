#ifndef SDIZO2_ARRAYITERATOR_H
#define SDIZO2_ARRAYITERATOR_H

template <typename T>
class Array;

template <typename T>
class ArrayIterator {
public:
    ArrayIterator(Array<T>* owningArray) : owner{owningArray} {};
    T& next();
    void remove();
    bool hasNext();
private:
    Array<T>* owner;
    size_t index{0};
};

template<typename T>
T &ArrayIterator<T>::next() {
    index++;
    return (*owner)[index - 1];
}

template<typename T>
void ArrayIterator<T>::remove() {
    owner->removeAt(index - 1);
    index--;
}

template<typename T>
bool ArrayIterator<T>::hasNext() {
    return index <= owner->getLength();
}


#endif //SDIZO2_ARRAYITERATOR_H
