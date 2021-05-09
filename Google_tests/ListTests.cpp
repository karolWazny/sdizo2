
#include "gtest/gtest.h"
#include "../structure_templates_lib/linked_list_lib/LinkedList.h"

TEST(LinkedListTestSuite, ContainsFalse){ // 12/0/2020 -> 0
    auto list = LinkedList<int>();
    ASSERT_FALSE(list.contains(5));
    ASSERT_TRUE(list.isEmpty());
}

TEST(LinkedListTestSuite, ContainsTrue){ // 12/0/2020 -> 0
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        ASSERT_EQ(list.getLength(), i);
        ASSERT_FALSE(list.contains(i));
        list.pushBack(i);
        ASSERT_TRUE(list.contains(i));
        ASSERT_FALSE(list.isEmpty());
        ASSERT_EQ(list.getLength(), i+1);
    }
    ASSERT_TRUE(list.contains(3));
}

TEST(LinkedListTestSuite, PushFront){ // 12/0/2020 -> 0
    auto list = LinkedList<int>();
    list.pushFront(5);
    ASSERT_TRUE(list.get(0) == 5);
    list.pushFront(4);
    ASSERT_TRUE(list.get(1) == 5);
    ASSERT_TRUE(list.get(0) == 4);
}

TEST(LinkedListTestSuite, PushBack){ // 12/0/2020 -> 0
    auto list = LinkedList<int>();
    list.pushBack(5);
    ASSERT_TRUE(list.get(0) == 5);
    list.pushBack(4);
    ASSERT_TRUE(list.get(0) == 5);
    ASSERT_TRUE(list.get(1) == 4);
    ASSERT_TRUE(list.getLength() == 2);
}

TEST(LinkedListTestSuite, PutAfterInTheMiddle){ // 12/0/2020 -> 0
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    list.putAfter(3, 8);
    ASSERT_TRUE(list.get(4) == 8);
}

TEST(LinkedListTestSuite, PutAfterLast){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    list.putAfter(4, 8);
    ASSERT_TRUE(list.get(5) == 8);
    ASSERT_TRUE(list.removeLast() == 8);
}

TEST(LinkedListTestSuite, PutAfterAbsent){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    list.putAfter(10, 8);
    ASSERT_TRUE(list.get(0) == 8);
    ASSERT_TRUE(list.get(1) == 0);
}

TEST(LinkedListTestSuite, RemoveMiddle){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    list.remove(3);
    ASSERT_TRUE(list.getLength() == 4);
    ASSERT_TRUE(list.get(3) == 4);
}

TEST(LinkedListTestSuite, RemoveFirst){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    ASSERT_TRUE(list.removeFirst() == 0);
    ASSERT_TRUE(list.getLength() == 4);
    ASSERT_TRUE(list.get(0) == 1);
}

TEST(LinkedListTestSuite, RemoveLast){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    ASSERT_TRUE(list.removeLast() == 4);
    ASSERT_TRUE(list.getLength() == 4);
    ASSERT_TRUE(list.removeLast() == 3);
}

TEST(LinkedListTestSuite, IsEmptyTrue){
    auto list = LinkedList<int>();
    ASSERT_TRUE(list.isEmpty());
}

TEST(LinkedListTestSuite, IsEmptyFalse){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    ASSERT_FALSE(list.isEmpty());
}

TEST(LinkedListTestSuite, SwapNeighbours){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    list.swap(2,3);
    ASSERT_TRUE(list.get(2) == 3);
    ASSERT_TRUE(list.get(3) == 2);
}

TEST(LinkedListTestSuite, SwapWithTheFirst){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    list.swap(0,3);
    ASSERT_TRUE(list.get(0) == 3);
    ASSERT_TRUE(list.get(3) == 0);
}

TEST(LinkedListTestSuite, SwapWithTheLast){
    auto list = LinkedList<int>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(i);
    }
    list.swap(1,4);
    ASSERT_EQ(list.get(1), 4);
    ASSERT_EQ(list.removeLast(), 1);
}

TEST(LinkedListTestSuite, RemoveFirstLot){
    auto list = LinkedList<int>();
    for(int i = 0; i < 150; i++)
    {
        list.pushBack(i);
        for(int k = 0; k <= i; k++)
        {
            ASSERT_TRUE(list.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(list.contains(k));
        }
    }
    while(!list.isEmpty())
    {
        list.removeFirst();
    }
}

TEST(LinkedListTestSuite, RemoveLastLot){
    auto list = LinkedList<int>();
    for(int i = 0; i < 150; i++)
    {
        list.pushBack(i);
        for(int k = 0; k <= i; k++)
        {
            ASSERT_TRUE(list.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(list.contains(k));
        }
    }
    while(!list.isEmpty())
    {
        list.removeLast();
    }
}

TEST(LinkedListTestSuite, PutAfterLength){
    auto list = LinkedList<int>();
    for(int i = 0; i < 150; i++)
    {
        list.pushBack(i);
        for(int k = 0; k <= i; k++)
        {
            ASSERT_TRUE(list.contains(k));
        }
        for(int k = i + 1; k < 150; k++)
        {
            ASSERT_FALSE(list.contains(k));
        }
    }
    ASSERT_EQ(list.getLength(), 150);
    list.putAfter(10, 40);
    ASSERT_EQ(list.getLength(), 151);
}

TEST(LinkedListTestSuite, NestedList){
    auto list = LinkedList<LinkedList<int>>();
    for(int i = 0; i < 5; i++)
    {
        list.pushBack(LinkedList<int>());
    }
    ASSERT_EQ(list.get(0).getLength(), 0);
    list.get(0).pushBack(5);
    ASSERT_EQ(list.get(0).getLength(), 1);
    ASSERT_EQ(list.get(0).get(0), 5);
    auto list2 = list.get(0);
    list2.pushBack(3);
    ASSERT_EQ(list.get(0).get(1), 3);
}