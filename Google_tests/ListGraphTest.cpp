#include "gtest/gtest.h"
#include "../graphs/ListGraph.h"

TEST(ListGraphSuite, AddVertex){
    auto graph = ListGraph();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
}

TEST(ListGraphSuite, AddEdge){
    auto graph = ListGraph();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
    graph.addEdge(0, 2, 8);
}
