#ifndef SDIZO_1_BINARYHEAP_H
#define SDIZO_1_BINARYHEAP_H

#include <memory>
#include <string>

//szablona klasy kopca binarnego (implementacja tablicowa)
template <typename T>
class BinaryHeap
{
public:
    BinaryHeap();
    void add(T element);
    bool remove(T element);
    bool contains(T element);
    T getMax();
    T extractMax();
    int getSize();
    std::string getRepresentation();
private:
    std::unique_ptr<T[]> content;
    int size;
    void reallocateContent();
    void cascadeUp();
    void cascadeDownFrom(int position);
    void swap(int position1, int position2);
    int calculateParentPosition(int childPosition);
    int findPositionOfElementInSubtree(int subtreeRootPosition, T element);
    int calculateLeftChildPosition(int parentPosition);
    int calculateRightChildPosition(int parentPosition);
};

template<typename T>
BinaryHeap<T>::BinaryHeap() {
    size = 0;
    reallocateContent();
}

//metoda dodania elementu do kopca
template<typename T>
void BinaryHeap<T>::add(T element) {
    size++;
    reallocateContent();
    content[size - 1] = element;
    cascadeUp();
}

//metoda przenosząca kopiec przy zmianie rozmiaru
template<typename T>
void BinaryHeap<T>::reallocateContent() {
    auto buffer = std::make_unique<T[]>(size);
    for(int i = 0; i < size; i++)
    {
        buffer[i] = content[i];
    }
    content = std::move(buffer);
}

//odbudowanie własności kopca od dołu po dodaniu nowego elementu
template<typename T>
void BinaryHeap<T>::cascadeUp() {
    int childPosition = size - 1;
    int parentPosition = calculateParentPosition(childPosition);
    bool heapPropertyRestored = (content[childPosition] <= content[parentPosition]);
    while (!heapPropertyRestored)
    {
        swap(childPosition, parentPosition);
        childPosition = parentPosition;
        parentPosition = calculateParentPosition(childPosition);
        heapPropertyRestored = (content[childPosition] <= content[parentPosition]);
    }
}

//metoda pozwalająca zamienić dwa elementy miejscami
template<typename T>
void BinaryHeap<T>::swap(const int position1, const int position2) {
    T buffer = content[position1];
    content[position1] = content[position2];
    content[position2] = buffer;
}

//metoda obliczająca indeks rodzica danego elementu w tablicy
template<typename T>
int BinaryHeap<T>::calculateParentPosition(const int childPosition) {
    int parentPosition = (childPosition - 1) >> 1;
    if(parentPosition < 0)
    {
        parentPosition = 0;
    }
    return parentPosition;
}

//metoda usuwająca element po kluczu
template<typename T>
bool BinaryHeap<T>::remove(T element) {
    int position = findPositionOfElementInSubtree(0, element);
    if(position == -1)
        return false;
    size--;
    swap(position, size);
    cascadeDownFrom(position);
    reallocateContent();
    return true;
}

//metoda zwracająca indeks elementu o danej wartości w poddrzewie zaczynającym się od danego węzła;
//jeżeli poddrzewo nie zawiera elementu, zwraca -1
template<typename T>
int BinaryHeap<T>::findPositionOfElementInSubtree(const int subtreeRootPosition, T element) {
    if((subtreeRootPosition >= size) || (content[subtreeRootPosition] < element))
    {
        return -1;
    }
    if(content[subtreeRootPosition] == element)
    {
        return subtreeRootPosition;
    }
    int buffer = findPositionOfElementInSubtree(calculateLeftChildPosition(subtreeRootPosition),
                                                element);
    if(buffer > -1)
    {
        return buffer;
    }
    return findPositionOfElementInSubtree(calculateRightChildPosition(subtreeRootPosition),
                                          element);
}

template<typename T>
int BinaryHeap<T>::calculateLeftChildPosition(const int parentPosition) {
    return (parentPosition << 1) + 1;
}

template<typename T>
int BinaryHeap<T>::calculateRightChildPosition(const int parentPosition) {
    return calculateLeftChildPosition(parentPosition) + 1;
}


template<typename T>
bool BinaryHeap<T>::contains(T element) {
    return findPositionOfElementInSubtree(0, element) > -1;
}

//metoda przywracająca własność kopca po usunięciu eolementu z korzenia i zastąpieniu go
//ostatnim elementem w tablicy
template<typename T>
void BinaryHeap<T>::cascadeDownFrom(const int position) {
    int rightChildPosition = calculateRightChildPosition(position);
    int leftChildPosition = calculateLeftChildPosition(position);
    int biggerChildPosition;
    if(leftChildPosition >= size)
    {
        return;
    }
    if(rightChildPosition >= size)
    {
        biggerChildPosition = leftChildPosition;
    } else
    {
        biggerChildPosition = (content[leftChildPosition] > content[rightChildPosition] ? leftChildPosition : rightChildPosition);
    }
    if(content[biggerChildPosition] > content[position])
    {
        swap(biggerChildPosition, position);
        cascadeDownFrom(biggerChildPosition);
    }
}
//zwraca wartosc elementu w korzeniu
template<typename T>
T BinaryHeap<T>::getMax() {
    return content[0];
}
//usuwa i zwraca element z korzenia
template<typename T>
T BinaryHeap<T>::extractMax() {
    T out = getMax();
    size--;
    swap(0, size);
    cascadeDownFrom(0);
    reallocateContent();
    return out;
}

template<typename T>
int BinaryHeap<T>::getSize() {
    return size;
}
//zwraca reprezentacje stringową kopca; jak w tablicy
template<typename T>
std::string BinaryHeap<T>::getRepresentation() {
    std::string out;
    out += "[";
    if(size)
    {
        out += std::to_string(content[0]);
        for(int i = 1; i < size; i++)
        {
            out += ", ";
            out += std::to_string(content[i]);
        }
    }
    out += "]";
    return out;
}

#endif //SDIZO_1_BINARYHEAP_H
