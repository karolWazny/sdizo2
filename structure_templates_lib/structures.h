#ifndef SDIZO_1_STRUCTURES_H
#define SDIZO_1_STRUCTURES_H

#include "trees_lib/RedBlackTree.h"
#include "linked_list_lib/LinkedList.h"
#include "binary_heap_lib/BinaryHeap.h"
#include "array_lib/Array.h"
#include "trees_lib/AVLTree.h"

template <typename T>
using rbtree = RedBlackTree<T>;

template <typename T>
using list = LinkedList<T>;

template <typename T>
using heap = BinaryHeap<T>;

template <typename T>
using array = Array<T>;

#endif //SDIZO_1_STRUCTURES_H
