#include "gtest/gtest.h"
#include "../graphs/ListGraph.h"

TEST(ListGraphSuite, AddVertex){
    auto graph = ListGraph();
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 0);
    graph.addVertex(0);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 1);
    graph.addVertex(1);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
    graph.addVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 3);
}

TEST(ListGraphSuite, AddVertexUniqueId){
    auto graph = ListGraph();
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 0);
    graph.addVertex(0);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 1);
    graph.addVertex(0);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 1);
    graph.addVertex(1);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
    graph.addVertex(1);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
}

TEST(ListGraphSuite, AddEdge){
    auto graph = ListGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    graph.addEdge(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
}

TEST(ListGraphSuite, RemoveEdge){
    auto graph = ListGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    graph.addEdge(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeEdge(0, 2);
    ASSERT_EQ(graph.edgesAmount(), 0);
}

TEST(ListGraphSuite, RemoveVertex){
    auto graph = ListGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
}

TEST(ListGraphSuite, Dijkstra){
    auto graph = ListGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
    auto mst = graph.MSTDijkstra();
    ASSERT_EQ(mst->edgesAmount(), 0);
    ASSERT_EQ(mst->verticesAmount(), 2);
}

TEST(ListGraphSuite, Dijkstra2){
    auto graph = ListGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(0, 2, 8);
    auto mst = graph.MSTDijkstra();
    ASSERT_EQ(mst->edgesAmount(), 1);
    ASSERT_EQ(mst->verticesAmount(), 3);
}