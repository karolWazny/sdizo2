#include "gtest/gtest.h"
#include "../graphs/ListGraph.h"

TEST(ListGraphSuite, AddVertex){
    auto graph = ListGraph();
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 0);
    graph.addVertex();
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 1);
    graph.addVertex();
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
    graph.addVertex();
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 3);
}

TEST(ListGraphSuite, AddEdge){
    auto graph = ListGraph();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
    ASSERT_EQ(graph.edgesAmount(), 0);
    graph.addEdge(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
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