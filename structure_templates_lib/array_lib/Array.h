#ifndef SDIZO_1_ARRAY_H
#define SDIZO_1_ARRAY_H
#include <memory>
#include <string>
#include <functional>

//szablon klasy implementującej tablicę dynamiczną
template <typename T>
class Array
{
public:
    Array<T>();
    Array<T>(size_t initialSize);
    void putAtPosition(T, const size_t);
    void swap(const size_t, const size_t);
    T removeAt(const size_t index);
    void pushBack(T);
    bool contains(T element);
    void pushFront(T);
    T removeLast();
    T removeFirst();
    T get(const size_t index);
    bool isEmpty();
    size_t getLength();
    std::string toString();
    T& operator[](size_t);
    size_t forEach(std::function<bool(T&)>);
    T& find(std::function<bool(T)> condition);
private:
    std::unique_ptr<T[]> elements;
    size_t length;
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
T Array<T>::get(const size_t index)
{
    if(index >= length)
        throw IndexOutOfBoundException();
    return elements[index];
}

//metoda do usuwania elementu po indeksie
template <typename T>
T Array<T>::removeAt(const size_t index)
{
    auto buffer = elements[index];
    auto newArray = std::make_unique<T[]>(length - 1);
    for(size_t i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for(size_t i = index + 1; i < length; i++)
    {
        newArray[i-1] = elements[i];
    }
    elements = std::move(newArray);
    length--;
    return buffer;
}

//metoda do zamiany dwóch elementów miejscami
template<typename T>
void Array<T>::swap(const size_t index1, const size_t index2)
{
    const auto buffer = elements[index1];
    elements[index1] = elements[index2];
    elements[index2] = buffer;
}

//metoda wstawiająca nowy element na danej pozycji
template<typename T>
void Array<T>::putAtPosition(T element, const size_t index)
{
    if(index > length)
    {
        throw IndexOutOfBoundException();
    }
    auto newArray = std::make_unique<T[]>(length + 1);
    for(size_t i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for(size_t i = index; i < length; i++)
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
size_t Array<T>::getLength()
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
    for(size_t i = 1; i < length; i++)
    {
        output += ", " + std::to_string(elements[i]);
    }
    output += "]";
    return output;
}

template<typename T>
bool Array<T>::contains(T element) {
    for(size_t i = 0; i < length; i++)
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
Array<T>::Array(size_t initialSize) {
    length = initialSize;
    elements = std::make_unique<T[]>(initialSize);
}

//operator dostępu do elementu po indeksie;
//zwraca obiekt przez referencję, działanie jak
//ten sam operator dla tablicy
template<typename T>
T &Array<T>::operator[](size_t index) {
    if(index >= length)
        throw IndexOutOfBoundException();
    return elements[index];
}

template<typename T>
size_t Array<T>::forEach(std::function<bool(T &)> function) {
    size_t count{};
    for(size_t i = 0; i < length; i++) {
        if(function(elements[i]))
            count++;
    }
    return count;
}

template<typename T>
T &Array<T>::find(std::function<bool(T)> condition) {
    for(size_t i = 0; i < length; i++) {
        if(condition(elements[i]))
            return elements[i];
    }
    throw std::exception();
}

#endif //SDIZO_1_ARRAY_H
