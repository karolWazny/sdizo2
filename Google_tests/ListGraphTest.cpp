#include "gtest/gtest.h"
#include "../graphs/ListGraph.h"

ListGraph testInstance(){
    auto graph = ListGraph(8);
    for(int i = 0; i < 8; i++)
    {
        graph.addVertex(i);
    }
    graph.addEdgeUndirected(0, 7, 16);

    graph.addEdgeUndirected(4, 5, 35);

    graph.addEdgeUndirected(4, 7, 37);

    graph.addEdgeUndirected(5, 7, 28);

    graph.addEdgeUndirected(1, 5, 32);

    graph.addEdgeUndirected(0, 4, 38);

    graph.addEdgeUndirected(2, 3, 17);

    graph.addEdgeUndirected(1, 7, 19);

    graph.addEdgeUndirected(0, 2, 26);

    graph.addEdgeUndirected(1, 2, 36);

    graph.addEdgeUndirected(1, 3, 29);

    graph.addEdgeUndirected(2, 7, 34);

    graph.addEdgeUndirected(2, 6, 40);

    graph.addEdgeUndirected(3, 6, 52);

    graph.addEdgeUndirected(0, 6, 58);

    graph.addEdgeUndirected(6, 4, 93);

    return graph;
}

TEST(ListGraphSuite, AddEdge){
    auto graph = ListGraph(3);
    ASSERT_EQ(graph.edgesAmount(), 0);
    graph.addEdgeDirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
}

TEST(ListGraphSuite, RemoveEdge){
    auto graph = ListGraph(3);
    ASSERT_EQ(graph.edgesAmount(), 0);
    graph.addEdgeDirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeEdgeDirected(0, 2);
    ASSERT_EQ(graph.edgesAmount(), 0);
}

TEST(ListGraphSuite, Prim){
    auto graph = ListGraph(2);
    graph.addVertex(0);
    graph.addVertex(1);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 0);
    ASSERT_EQ(mst->verticesAmount(), 2);
}

TEST(ListGraphSuite, Prim2){
    auto graph = ListGraph(3);
    graph.addEdgeUndirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 2);
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 2);
    ASSERT_EQ(mst->verticesAmount(), 3);
}

TEST(ListGraphSuite, Prim3){
    auto graph = ListGraph(3);
    graph.addEdgeUndirected(0, 2, 8);
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 2);
    ASSERT_EQ(mst->verticesAmount(), 3);
}

TEST(ListGraphSuite, PrimFullTestCase){
    auto graph = testInstance();
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 14);
    ASSERT_EQ(mst->verticesAmount(), 8);
}

TEST(ListGraphSuite, Kruskal){
    auto graph = ListGraph(2);
    graph.addEdgeDirected(0, 1, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    ASSERT_EQ(graph.verticesAmount(), 2);
    auto mst = graph.MSTKruskal();
    ASSERT_EQ(mst->edgesAmount(), 2);
    ASSERT_EQ(mst->verticesAmount(), 2);
}

TEST(ListGraphSuite, Kruskal2){
    auto graph = ListGraph(3);
    graph.addEdgeUndirected(0, 2, 8);
    auto mst = graph.MSTKruskal();
    ASSERT_EQ(mst->edgesAmount(), 2);
    ASSERT_EQ(mst->verticesAmount(), 3);
}

TEST(ListGraphSuite, KruskalFullTestCase){
    auto graph = testInstance();

    auto mst = graph.MSTKruskal();
    ASSERT_EQ(mst->edgesAmount(), 14);
    ASSERT_EQ(mst->verticesAmount(), 8);
}

TEST(ListGraphSuite, Dijkstra) {
    auto graph = testInstance();
    auto path = graph.shortestPathDijkstra(0, 7);
    ASSERT_EQ(path->totalWeight, 16);
}

TEST(ListGraphSuite, Dijkstra2) {
    auto graph = testInstance();
    auto path = graph.shortestPathDijkstra(2, 3);
    ASSERT_EQ(path->totalWeight, 17);
}

TEST(ListGraphSuite, BelmanFord) {
    auto graph = testInstance();
    auto path = graph.shortestPathBF(0, 7);
    ASSERT_EQ(path->totalWeight, 16);
}

TEST(ListGraphSuite, BelmanFord3) {
    auto graph = testInstance();
    auto path = graph.shortestPathBF(7, 0);
    ASSERT_EQ(path->totalWeight, 16);
}

TEST(ListGraphSuite, BelmanFord2) {
    auto graph = testInstance();
    auto path = graph.shortestPathBF(2, 3);
    ASSERT_EQ(path->totalWeight, 17);
}

TEST(ListGraphSuite, ShortestPathCountOff) {
    auto graph = testInstance();
    for(int i = 0; i < 8; i++) {
        for(int k = 0; k < 8; k++) {
            ASSERT_EQ(graph.shortestPathDijkstra(i, k)->totalWeight,
                      graph.shortestPathDijkstra(k, i)->totalWeight);
            ASSERT_EQ(graph.shortestPathBF(i, k)->totalWeight,
                      graph.shortestPathBF(k, i)->totalWeight);
            ASSERT_EQ(graph.shortestPathBF(i, k)->totalWeight,
                      graph.shortestPathDijkstra(i, k)->totalWeight);
        }
    }
}