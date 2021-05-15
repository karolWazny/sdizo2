#include "gtest/gtest.h"
#include "../graphs/MatrixGraph.h"

MatrixGraph testInstance(){
    auto graph = MatrixGraph();
    for(int i = 0; i < 8; i++)
    {
        graph.addVertex(i);
    }
    graph.addEdgeDirected(0, 7, 16);
    graph.addEdgeDirected(7, 0, 16);

    graph.addEdgeDirected(4, 5, 35);
    graph.addEdgeDirected(5, 4, 35);

    graph.addEdgeDirected(4, 7, 37);
    graph.addEdgeDirected(7, 4, 37);

    graph.addEdgeDirected(5, 7, 28);
    graph.addEdgeDirected(7, 5, 28);

    graph.addEdgeDirected(1, 5, 32);
    graph.addEdgeDirected(5, 1, 32);

    graph.addEdgeDirected(0, 4, 38);
    graph.addEdgeDirected(4, 0, 38);

    graph.addEdgeDirected(2, 3, 17);
    graph.addEdgeDirected(3, 2, 17);

    graph.addEdgeDirected(1, 7, 19);
    graph.addEdgeDirected(7, 1, 19);

    graph.addEdgeDirected(0, 2, 26);
    graph.addEdgeDirected(2, 0, 26);

    graph.addEdgeDirected(1, 2, 36);
    graph.addEdgeDirected(2, 1, 36);

    graph.addEdgeDirected(1, 3, 29);
    graph.addEdgeDirected(3, 1, 29);

    graph.addEdgeDirected(2, 7, 34);
    graph.addEdgeDirected(7, 2, 34);

    graph.addEdgeDirected(2, 6, 40);
    graph.addEdgeDirected(6, 2, 40);

    graph.addEdgeDirected(3, 6, 52);
    graph.addEdgeDirected(6, 3, 52);

    graph.addEdgeDirected(0, 6, 58);
    graph.addEdgeDirected(6, 0, 58);

    graph.addEdgeDirected(6, 4, 93);
    graph.addEdgeDirected(4, 6, 93);

    return graph;
}

TEST(MatrixGraphSuite, AddVertex){
    auto graph = MatrixGraph();
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

TEST(MatrixGraphSuite, AddVertexUniqueId){
    auto graph = MatrixGraph();
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

TEST(MatrixGraphSuite, AddEdge){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    graph.addEdgeDirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
}

TEST(MatrixGraphSuite, RemoveEdge){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    graph.addEdgeDirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeEdgeDirected(0, 2);
    ASSERT_EQ(graph.edgesAmount(), 0);
}

TEST(MatrixGraphSuite, RemoveVertex){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdgeDirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
}

TEST(MatrixGraphSuite, Prim){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdgeUndirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 0);
    ASSERT_EQ(mst->verticesAmount(), 2);
}

TEST(MatrixGraphSuite, Prim2){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdgeUndirected(0, 2, 8);
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 1);
    ASSERT_EQ(mst->verticesAmount(), 3);
}

TEST(MatrixGraphSuite, Prim3){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdgeUndirected(0, 2, 8);
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 1);
    ASSERT_EQ(mst->verticesAmount(), 3);
}

TEST(MatrixGraphSuite, PrimFullTestCase){
    auto graph = testInstance();
    auto mst = graph.MSTPrim();
    ASSERT_EQ(mst->edgesAmount(), 7);
    ASSERT_EQ(mst->verticesAmount(), 8);
}

TEST(MatrixGraphSuite, Kruskal){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdgeDirected(0, 2, 8);
    ASSERT_EQ(graph.edgesAmount(), 1);
    graph.removeVertex(2);
    ASSERT_EQ(graph.edgesAmount(), 0);
    ASSERT_EQ(graph.verticesAmount(), 2);
    auto mst = graph.MSTKruskal();
    ASSERT_EQ(mst->edgesAmount(), 0);
    ASSERT_EQ(mst->verticesAmount(), 2);
}

TEST(MatrixGraphSuite, Kruskal2){
    auto graph = MatrixGraph();
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdgeDirected(0, 2, 8);
    graph.addEdgeDirected(2, 0, 8);
    auto mst = graph.MSTKruskal();
    ASSERT_EQ(mst->edgesAmount(), 2);
    ASSERT_EQ(mst->verticesAmount(), 3);
}

TEST(MatrixGraphSuite, KruskalFullTestCase){
    auto graph = testInstance();

    auto mst = graph.MSTKruskal();
    ASSERT_EQ(mst->edgesAmount(), 14);
    ASSERT_EQ(mst->verticesAmount(), 8);
}

/*TEST(MatrixGraphSuite, Dijkstra) {
    auto graph = testInstance();
    auto path = graph.shortestPathDijkstra(0, 7);
    ASSERT_EQ(path->totalWeight, 16);
}

TEST(MatrixGraphSuite, Dijkstra2) {
    auto graph = testInstance();
    auto path = graph.shortestPathDijkstra(2, 3);
    ASSERT_EQ(path->totalWeight, 17);
}

TEST(MatrixGraphSuite, BelmanFord) {
    auto graph = testInstance();
    auto path = graph.shortestPathBF(0, 7);
    ASSERT_EQ(path->totalWeight, 16);
}

TEST(MatrixGraphSuite, BelmanFord3) {
    auto graph = testInstance();
    auto path = graph.shortestPathBF(7, 0);
    ASSERT_EQ(path->totalWeight, 16);
}

TEST(MatrixGraphSuite, BelmanFord2) {
    auto graph = testInstance();
    auto path = graph.shortestPathBF(2, 3);
    ASSERT_EQ(path->totalWeight, 17);
}

TEST(MatrixGraphSuite, ShortestPathCountOff) {
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
}*/
