#ifndef SDIZO2_FIXEDMINIMUMHEAP_H
#define SDIZO2_FIXEDMINIMUMHEAP_H

#include <functional>

template <typename T>
class FixedMinimumHeap
{
public:
    explicit FixedMinimumHeap(size_t size);
    void add(T element);
    bool remove(T element);
    bool contains(T element);
    T getRoot();
    T extractRoot();
    size_t getSize();
    std::string getRepresentation();
    void removeWhere(std::function<bool(T)>);
private:
    std::unique_ptr<T[]> content{};
    size_t size{0};
    size_t maxSize;
    void cascadeUp();
    void cascadeDownFrom(size_t position);
    void swap(size_t position1, size_t position2);
    size_t calculateParentPosition(size_t childPosition);
    size_t findPositionOf(T element);
    size_t calculateLeftChildPosition(size_t parentPosition);
    size_t calculateRightChildPosition(size_t parentPosition);
    bool removeAtPosition(size_t);
};

template<typename T>
FixedMinimumHeap<T>::FixedMinimumHeap(size_t size) : maxSize{size} {
    this->content = std::unique_ptr<T[]>(new T[size]);
}

//metoda dodania elementu do kopca
template<typename T>
void FixedMinimumHeap<T>::add(T element) {
    if(size == maxSize)
        throw std::exception();
    size++;
    content[size - 1] = element;
    cascadeUp();
}

//odbudowanie własności kopca od dołu po dodaniu nowego elementu
template<typename T>
void FixedMinimumHeap<T>::cascadeUp() {
    size_t childPosition = size - 1;
    size_t parentPosition = calculateParentPosition(childPosition);
    bool heapPropertyRestored = (content[childPosition] >= content[parentPosition]);
    while (!heapPropertyRestored)
    {
        swap(childPosition, parentPosition);
        childPosition = parentPosition;
        parentPosition = calculateParentPosition(childPosition);
        heapPropertyRestored = (content[childPosition] >= content[parentPosition]);
    }
}

//metoda pozwalająca zamienić dwa elementy miejscami
template<typename T>
void FixedMinimumHeap<T>::swap(const size_t position1, const size_t position2) {
    T buffer = content[position1];
    content[position1] = content[position2];
    content[position2] = buffer;
}

//metoda obliczająca indeks rodzica danego elementu w tablicy
template<typename T>
size_t FixedMinimumHeap<T>::calculateParentPosition(const size_t childPosition) {
    if(childPosition == 0)
        return 0;
    size_t parentPosition = (childPosition - 1) >> 1;
    return parentPosition;
}

//metoda usuwająca element po kluczu
template<typename T>
bool FixedMinimumHeap<T>::remove(T element) {
    size_t position = findPositionOf(element);
    return removeAtPosition(position);
}

template<typename T>
bool FixedMinimumHeap<T>::removeAtPosition(size_t position) {
    if(position == -1)
        return false;
    size--;
    swap(position, size);
    cascadeDownFrom(position);
    return true;
}

//metoda zwracająca indeks elementu o danej wartości w poddrzewie zaczynającym się od danego węzła;
//jeżeli poddrzewo nie zawiera elementu, zwraca -1
template<typename T>
size_t FixedMinimumHeap<T>::findPositionOf(T element) {
    for(size_t i = 0; i < size; i++)
    {
        if(element == content[i])
            return i;
    }
    return -1;
}

template<typename T>
size_t FixedMinimumHeap<T>::calculateLeftChildPosition(const size_t parentPosition) {
    return (parentPosition << 1) + 1;
}

template<typename T>
size_t FixedMinimumHeap<T>::calculateRightChildPosition(const size_t parentPosition) {
    return calculateLeftChildPosition(parentPosition) + 1;
}


template<typename T>
bool FixedMinimumHeap<T>::contains(T element) {
    return findPositionOf(element) > -1;
}

//metoda przywracająca własność kopca po usunięciu eolementu z korzenia i zastąpieniu go
//ostatnim elementem w tablicy
template<typename T>
void FixedMinimumHeap<T>::cascadeDownFrom(const size_t position) {
    size_t rightChildPosition = calculateRightChildPosition(position);
    size_t leftChildPosition = calculateLeftChildPosition(position);
    size_t smallerChildPosition;
    if(leftChildPosition >= size)
    {
        return;
    }
    if(rightChildPosition >= size)
    {
        smallerChildPosition = leftChildPosition;
    } else {
        smallerChildPosition = (content[leftChildPosition] < content[rightChildPosition] ? leftChildPosition : rightChildPosition);
    }
    if(content[smallerChildPosition] < content[position])
    {
        swap(smallerChildPosition, position);
        cascadeDownFrom(smallerChildPosition);
    }
}
//zwraca wartosc elementu w korzeniu
template<typename T>
T FixedMinimumHeap<T>::getRoot() {
    return content[0];
}
//usuwa i zwraca element z korzenia
template<typename T>
T FixedMinimumHeap<T>::extractRoot() {
    T out = getRoot();
    size--;
    swap(0, size);
    cascadeDownFrom(0);
    return out;
}

template<typename T>
size_t FixedMinimumHeap<T>::getSize() {
    return size;
}
//zwraca reprezentacje stringową kopca; jak w tablicy
template<typename T>
std::string FixedMinimumHeap<T>::getRepresentation() {
    std::string out;
    out += "[";
    if(size)
    {
        out += std::to_string(content[0]);
        for(size_t i = 1; i < size; i++)
        {
            out += ", ";
            out += std::to_string(content[i]);
        }
    }
    out += "]";
    return out;
}

template<typename T>
void FixedMinimumHeap<T>::removeWhere(std::function<bool(T)> decider) {
    for(long i = size - 1; i >= 0; i--) {
        if(decider(content[i]))
        {
            removeAtPosition(i);
        }
    }
}

#endif //SDIZO2_FIXEDMINIMUMHEAP_H
