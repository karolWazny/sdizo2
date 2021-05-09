#ifndef SDIZO_1_LINKEDLIST_H
#define SDIZO_1_LINKEDLIST_H

#include "LinkedListItem.h"
#include "ListIterator.h"
#include <string>

//szablon klasy listy podwójnie wiązanej
template <typename type>
class LinkedList
{
    friend ListIterator<type>;
public:
    ListIterator<type> iterator();
    int firstIndexOf(type element);
    bool contains(type element);
    void addAtPosition(type, int);
    void putAfter(type whereToPut, type elementToAdd);
    void swap(int, int) noexcept (false);
    type removeAt(int index);
    bool remove(type element);
    void pushBack(type);
    void pushFront(type);
    type removeLast();
    type removeFirst();
    type& get(int index);
    bool isEmpty();
    int getLength();
    LinkedList();
    class Nexter : public  INextable<type> {
    public:
        std::shared_ptr<INextable<type>> pointer;
        std::weak_ptr<INextable<type>> mThis;
        Nexter();
        void setMThis(std::shared_ptr<INextable<type>> mThis);
        std::shared_ptr<INextable<type>> getNext() override;
        void setNext(std::shared_ptr<INextable<type>> next) override;
        void putAfter(type element) override;
        bool hasNext() override;
    };
    std::string toString();
private:
    std::weak_ptr<INextable<type>> lastIndex;
    //wartownik trzymający wskaźnik na pierwszy element;
    //ułatwia obsługę dodawania i usuwania pierwszego elementu
    std::shared_ptr< Nexter > guard;
    int length;
    std::shared_ptr< INextable<type> > getItem(int index);
};
//dostęp do elementu listy na danej pozycji
template<typename type>
std::shared_ptr< INextable<type> > LinkedList<type>::getItem(const int index)
{
    int counter = 0;
    auto buffer = guard->getNext();
    while (counter < index) {
        buffer = buffer->getNext();
        counter++;
    }
    return buffer;
}

//dodanie elementu na danej pozycji
template<typename type>
void LinkedList<type>::addAtPosition(type content, int index)
{
    if (!index) {
        pushFront(content);
        return;
    }
    else {
        auto buffer = getItem(index - 1);
        buffer->putAfter(content);
        length++;
    }
}

//zamiana dwóch elementów miejscami
template<typename type>
void LinkedList<type>::swap(int index1, int index2) noexcept(false)
{
    if (index1 == index2) {
        return;
    }
    if (index1 > index2) {
        auto buffer = index1;
        index1 = index2;
        index2 = buffer;
    }

    auto buffer = guard->getNext();
    int count = 0;
    while (count < index1) {
        buffer = buffer->getNext();
        count++;
    }
    auto item_1 = buffer;
    while (count < index2) {
        buffer = buffer->getNext();
        count++;
    }
    auto item_2 = buffer;
    item_1->swap(item_2);
    if(index2 == length - 1)
    {
        lastIndex = item_1;
    }
}

//usunięcie elementu na danej pozycji
template<typename type>
type LinkedList<type>::removeAt(int index)
{
    auto buffer = getItem(index);
    auto out = buffer->getContent();
    buffer->remove();
    length--;
    return out;
}

//dodanie elementu na końcu listy
template<typename type>
void LinkedList<type>::pushBack(type element)
{
    if (!length) {
        guard->setNext(std::shared_ptr<LinkedListItem<type>>(new LinkedListItem<type>(element, guard)));
        lastIndex = guard->getNext();
    }
    else {
        lastIndex.lock()->putAfter(element);
        lastIndex = lastIndex.lock()->getNext();
    }
    length++;
}

//dodanie elementu na początku listy
template <typename T>
void LinkedList<T>::pushFront(T element)
{
    if(!isEmpty())
    {
        guard->putAfter(element);
    } else
    {
        guard->putAfter(element);
        lastIndex = guard->getNext();
    }
    length++;
}

//usunięcie elementu z głowy listy
template <typename T>
T LinkedList<T>::removeFirst()
{
    return removeAt(0);
}

//usunięcie elementu z ogona
template <typename T>
T LinkedList<T>::removeLast()
{
    auto buffer = lastIndex.lock();
    lastIndex = buffer->getPrevious();
    buffer->remove();
    length--;
    return buffer->getContent();
}

//dostęp do klucza w elemencie na danej pozycji
template<typename type>
type& LinkedList<type>::get(int index) {
    return getItem(index)->getContent();
}

template<typename type>
bool LinkedList<type>::isEmpty()
{
    return !length;
}

template<typename type>
int LinkedList<type>::getLength()
{
    return length;
}

template<typename type>
LinkedList<type>::LinkedList()
{
    length = 0;
    guard = std::make_unique<Nexter>();
    guard->setMThis(guard);
}
//definicja klasy wewnętrznej -  strażnika
//trzymającego wskaźnik na pierwszy element;
//implementuje ten sam interfejs co elementy listy
template<typename type>
LinkedList<type>::Nexter::Nexter()
{
    pointer = std::shared_ptr<LinkedListItem<type>>(nullptr);
}

template<typename type>
std::shared_ptr<INextable<type>> LinkedList<type>::Nexter::getNext()
{
    return pointer;
}

template<typename type>
void LinkedList<type>::Nexter::setNext(std::shared_ptr<INextable<type>> next)
{
    pointer = next;
}

template<typename type>
bool LinkedList<type>::Nexter::hasNext()
{
    return pointer != nullptr;
}

//metoda strażnika tworząca i wstawiająca nowy element listy
//o zadanym kluczu za strażnikiem
template<typename type>
void LinkedList<type>::Nexter::putAfter(type element) {
    auto buffer = std::make_shared<LinkedListItem<type>>(element);
    if (pointer != nullptr) {
        buffer->setNext(pointer);
        pointer->setPrevious(buffer);
    }
    buffer->setPrevious(mThis);
    pointer = buffer;
}

template<typename type>
void LinkedList<type>::Nexter::setMThis(std::shared_ptr<INextable<type>> mThis) {
    this->mThis = mThis;
}

template<typename T>
std::string LinkedList<T>::toString()
{
    std::string output = "[";
    if(!isEmpty())
    {
        auto buffer = guard->getNext();
        output += std::to_string(buffer->getContent());
        while(buffer->hasNext())
        {
            output += ", ";
            buffer = buffer->getNext();
            output += std::to_string(buffer->getContent());
        }
    }
    return output + "]";
}

//usunięcie elementu o danym kluczu
template<typename type>
bool LinkedList<type>::remove(type element)
{
    if(isEmpty())
    {
        return false;
    }
    auto buffer = guard->getNext();
    for(int i = 0; i < length; i++)
    {
        if(buffer->getContent() == element)
        {
            if(i == --length)
            {
                lastIndex = buffer->getPrevious();
            }
            buffer->remove();
            return true;
        }
        buffer = buffer->getNext();
    }
    return false;
}

// metoda wstawiająca nowy element listy za elementem o danym kluczu;
//jezeli ten klucz nie występuje w liście, element zostaje umieszczony na początku
template<typename type>
void LinkedList<type>::putAfter(type whereToPut, type elementToAdd)
{
    auto buffer = guard->getNext();
    for(int i = 0; i < length; i++)
    {
        if(buffer->getContent() == whereToPut)
        {
            buffer->putAfter(elementToAdd);
            if(i == length - 1)
            {
                lastIndex = buffer->getNext();
            }
            length++;
            return;
        }
        buffer = buffer->getNext();
    }
    pushFront(elementToAdd);
}

template<typename type>
bool LinkedList<type>::contains(type element) {
    std::shared_ptr<INextable<type>> currentItem = guard;
    while (currentItem->hasNext())
    {
        currentItem = currentItem->getNext();
        if(currentItem->getContent() == element)
        {
            return true;
        }
    }
    return false;
}

template<typename type>
int LinkedList<type>::firstIndexOf(type element) {
    if(isEmpty())
    {
        return -1;
    }
    auto buffer = guard->getNext();
    for(int i = 0; i < length; i++)
    {
        if(buffer->getContent() == element)
        {
            return i;
        }
        buffer = buffer->getNext();
    }
    return -1;
}

template<typename type>
ListIterator<type> LinkedList<type>::iterator() {
    return ListIterator<type>(this, guard);
}

#endif //SDIZO_1_LINKEDLIST_H