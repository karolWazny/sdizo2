#ifndef SDIZO_1_ARRAY_H
#define SDIZO_1_ARRAY_H
#include <memory>
#include <string>

//szablon klasy implementującej tablicę dynamiczną
template <typename T>
class Array
{
public:
    Array<T>();
    Array<T>(int initialSize);
    void putAtPosition(T, const int);
    void swap(const int, const int);
    T removeAt(const int index);
    void pushBack(T);
    bool contains(T element);
    void pushFront(T);
    T removeLast();
    T removeFirst();
    T get(const int index);
    bool isEmpty();
    int getLength();
    std::string toString();
    T& operator[](int);
private:
    std::unique_ptr<T[]> elements;
    int length;
};

//wyjątek oznaczający żądanie elementu o indeksie niebędącym w tablicy
class IndexOutOfBoundException : public std::exception
{

};


template <typename T>
Array<T>::Array()
{
    length = 0;
    elements = std::make_unique<T[]>(length);
}

//metoda do dodania elementu na końcu
template<typename T>
void Array<T>::pushBack(T element)
{
    putAtPosition(element, length);
}

//metoda do usunięcia elementu na początku
template <typename T>
T Array<T>::removeFirst()
{
    return removeAt(0);
}

//metoda usuwająca ostatni element
template <typename T>
T Array<T>::removeLast()
{
    return removeAt(length - 1);
}

//metoda dodająca element na początku tablicy
template <typename T>
void Array<T>::pushFront(T element)
{
    putAtPosition(element, 0);
}

//metoda zwracająca element o danym indeksie przez wartość
template <typename T>
T Array<T>::get(const int index)
{
    if(index >= length || index < 0)
        throw IndexOutOfBoundException();
    return elements[index];
}

//metoda do usuwania elementu po indeksie
template <typename T>
T Array<T>::removeAt(const int index)
{
    auto buffer = elements[index];
    auto newArray = std::make_unique<T[]>(length - 1);
    for(int i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for(int i = index + 1; i < length; i++)
    {
        newArray[i-1] = elements[i];
    }
    elements = std::move(newArray);
    length--;
    return buffer;
}

//metoda do zamiany dwóch elementów miejscami
template<typename T>
void Array<T>::swap(const int index1, const int index2)
{
    const auto buffer = elements[index1];
    elements[index1] = elements[index2];
    elements[index2] = buffer;
}

//metoda wstawiająca nowy element na danej pozycji
template<typename T>
void Array<T>::putAtPosition(T element, const int index)
{
    if(index > length)
    {
        throw IndexOutOfBoundException();
    }
    auto newArray = std::make_unique<T[]>(length + 1);
    for(int i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for(int i = index; i < length; i++)
    {
        newArray[i+1] = elements[i];
    }
    newArray[index] = element;
    elements = std::move(newArray);
    length++;
}

template <typename T>
bool Array<T>::isEmpty()
{
    return !length;
}

template <typename T>
int Array<T>::getLength()
{
    return length;
}

template <typename T>
std::string Array<T>::toString()
{
    std::string output = "[";
    if(length)
    {
        output += std::to_string(elements[0]);
    }
    for(int i = 1; i < length; i++)
    {
        output += ", " + std::to_string(elements[i]);
    }
    output += "]";
    return output;
}

template<typename T>
bool Array<T>::contains(T element) {
    for(int i = 0; i < length; i++)
    {
        if(element == elements[i])
        {
            return true;
        }
    }
    return false;
}

//metoda pozwalająca stworzyć tablicę zadanej wielkości;
//zaimplementowana aby umożliwić szybsze budowanie struktury
//z pliku i generowanie dużych tablic do testów
template<typename T>
Array<T>::Array(int initialSize) {
    length = initialSize;
    elements = std::make_unique<T[]>(initialSize);
}

//operator dostępu do elementu po indeksie;
//zwraca obiekt przez referencję, działanie jak
//ten sam operator dla tablicy
template<typename T>
T &Array<T>::operator[](int index) {
    if(index < 0 || index >= length)
        throw IndexOutOfBoundException();
    return elements[index];
}

#endif //SDIZO_1_ARRAY_H
