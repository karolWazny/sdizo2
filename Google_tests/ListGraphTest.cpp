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

TEST(ListGraphSuite, RemoveEdge){
    auto graph = ListGraph();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
    graph.addEdge(0, 2, 8);
    graph.removeEdge(0, 2);
}

TEST(ListGraphSuite, RemoveVertex){
    auto graph = ListGraph();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
    graph.addEdge(0, 2, 8);
    graph.removeVertex(2);
}