#ifndef SDIZO_1_LINKEDLISTITEM_H
#define SDIZO_1_LINKEDLISTITEM_H

#include "INextable.h"

//szablon klasy elementu listy
template <typename type>
class LinkedListItem : public INextable<type>
{
private:
    std::weak_ptr<INextable<type>> previous;
    type content;
    std::shared_ptr<INextable<type>> next;
    void putAfter(INextable<type>);
    class Swapper
    {
    public:
        explicit Swapper(LinkedListItem<type>* owningItem);
        void swapWith(std::shared_ptr<INextable<type>>);
    private:
        LinkedListItem<type>* owner;
        std::shared_ptr<INextable<type>> replacement;
        void swapPointersInPredecessors();
        void swapPointersToConsequents();
        void swapPointersInConsequents();
        void swapPointersToPredecessors();
    };
public:
    explicit LinkedListItem(type);
    LinkedListItem(type, std::shared_ptr<INextable<type>>);
    type getContent() override;
    std::shared_ptr<INextable<type>> getNext() override;
    void setNext(std::shared_ptr<INextable<type>> next) override;
    std::shared_ptr<INextable<type>> getPrevious() override;
    void setPrevious(std::weak_ptr<INextable<type>> newPrevious) override;
    void putAfter(type) override;
    void remove() override;
    void swap(std::shared_ptr<INextable<type>>) override;
    bool hasNext() override;
};
//klasa wewnętrzna odpowiedzialna za zamienianie elementów miejscami
template<typename type>
LinkedListItem<type>::Swapper::Swapper(LinkedListItem<type> *owningItem) {
    owner = owningItem;
}

template<typename type>
void LinkedListItem<type>::Swapper::swapWith(std::shared_ptr<INextable<type>>replacement) {
    this->replacement = replacement;
    auto replacementConsequent = replacement->getNext();
    swapPointersInPredecessors();
    swapPointersToConsequents();
    swapPointersInConsequents();
    swapPointersToPredecessors();
}
//drobne metody zamieniające wskaźniki, co skutkuje zamianą miejscami elementów w liście
template<typename type>
void LinkedListItem<type>::Swapper::swapPointersInPredecessors() {
    auto replacementPredecessor = replacement->getPrevious();
    replacementPredecessor->setNext(owner->previous.lock()->getNext());
    owner->previous.lock()->setNext(replacement);
}

template<typename type>
void LinkedListItem<type>::Swapper::swapPointersToConsequents() {
    auto pointerBuffer = replacement->getNext();
    replacement->setNext(owner->next);
    owner->next = pointerBuffer;
}

template<typename type>
void LinkedListItem<type>::Swapper::swapPointersInConsequents() {
    auto pointerBuffer = replacement->getNext()->getPrevious();
    if(owner->hasNext())
    {
        owner->next->setPrevious(pointerBuffer);
    }
    replacement->getNext()->setPrevious(replacement);
}

template<typename type>
void LinkedListItem<type>::Swapper::swapPointersToPredecessors() {
    auto pointerBuffer = replacement->getPrevious();
    replacement->setPrevious(owner->previous);
    owner->previous = pointerBuffer;
}

template <typename T>
bool LinkedListItem<T>::hasNext()
{
    return next != nullptr;
}

template <typename T>
void LinkedListItem<T>::setNext(std::shared_ptr<INextable<T>> next) {
    this->next = next;
}

template <typename T>
std::shared_ptr<INextable<T>> LinkedListItem<T>::getNext() {
    return next;
}

template<typename type>
void LinkedListItem<type>::swap(std::shared_ptr<INextable<type>>replacement) {

    Swapper swapper = Swapper(this);
    swapper.swapWith(replacement);
}

template<typename type>
type LinkedListItem<type>::getContent() {
    return content;
}

template<typename type>
LinkedListItem<type>::LinkedListItem(type content)
{
    this->content = content;
    next = std::shared_ptr<LinkedListItem<type>>(nullptr);
    previous = std::shared_ptr<INextable<type>>(nullptr);
}

template<typename type>
LinkedListItem<type>::LinkedListItem(type content, std::shared_ptr<INextable<type>> pointer)
{
    this->content = content;
    next = std::shared_ptr<LinkedListItem<type>>(nullptr);
    previous = pointer;
}
//metoda tworząca nowy element i umieszczająca go na pozycji kolejnej w liście
template<typename type>
void LinkedListItem<type>::putAfter(type nextItem)
{
    auto buffer = std::make_shared<LinkedListItem<type>>(nextItem);
    if (next != nullptr) {
        buffer->next = next;
        next->setPrevious(buffer);
    }
    buffer->previous = previous.lock()->getNext();
    next = buffer;
}

template<typename type>
void LinkedListItem<type>::remove()
{
    if(next != nullptr)
    {
        next->setPrevious(previous);
    }
    previous.lock()->setNext(next);
}

template<typename type>
void LinkedListItem<type>::putAfter(INextable<type> nextItem)
{
    auto buffer = next;
    next = std::shared_ptr<LinkedListItem<type>>(nextItem);
    buffer->previous = next;
    next->next = buffer;
    next->previous = std::weak_ptr<LinkedListItem<type>>(this);
}

template<typename type>
std::shared_ptr<INextable<type>> LinkedListItem<type>::getPrevious()
{
    return previous.lock();
}

template<typename type>
void LinkedListItem<type>::setPrevious(std::weak_ptr<INextable<type>> newPrevious) {
    previous = newPrevious;
}


#endif //SDIZO_1_LINKEDLISTITEM_H