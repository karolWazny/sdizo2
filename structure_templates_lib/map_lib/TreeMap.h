#ifndef SDIZO2_TREEMAP_H
#define SDIZO2_TREEMAP_H

template <typename T, typename U>
class TreeMap {
public:
    U& operator[](T);
};

template<typename T, typename U>
U &TreeMap<T, U>::operator[](T) {
    return <#initializer#>;
}

template <typename T, typename U>
struct TreeMapNode {
public:
    T key;
    U content;

};

template <typename T, typename U>
bool operator>=(TreeMapNode<T, U> m, TreeMapNode<T, U> n) {
    return m.key >= n.key;
}

template <typename T, typename U>
bool operator<=(TreeMapNode<T, U> m, TreeMapNode<T, U> n) {
    return m.key <= n.key;
}

template <typename T, typename U>
bool operator>(TreeMapNode<T, U> m, TreeMapNode<T, U> n) {
    return m.key > n.key;
}

template <typename T, typename U>
bool operator<(TreeMapNode<T, U> m, TreeMapNode<T, U> n) {
    return m.key < n.key;
}

template <typename T, typename U>
bool operator==(TreeMapNode<T, U> m, TreeMapNode<T, U> n) {
    return m.key == n.key;
}

#endif //SDIZO2_TREEMAP_H
