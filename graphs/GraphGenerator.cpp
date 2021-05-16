#include "GraphGenerator.h"

GraphPointer GraphGenerator::generateGraphDirected(const FactoryPointer factory,
                                                   const size_t vertices,
                                                   const unsigned char fulfilment) {
    GraphPointer graph;
    ListGraph referenceGraph(0);
    do {
        referenceGraph = ListGraph(vertices);
        graph = factory->build(vertices);
        unsigned long edgesFull = fullGraphEdgesDirected(vertices);
        unsigned long edgesInGraph = edgesFull * fulfilment / 100;
        for(size_t i = 0; i < vertices; i++) {
            for(size_t k = 0; k < vertices; k++) {
                if(i != k) {
                    if(randomizer.getBool(edgesInGraph, edgesFull)) {
                        graph->addEdgeDirected(i, k, randomizer.getInt(50));
                        referenceGraph.addEdgeDirected(i, k, 1);
                        edgesInGraph--;
                    }
                    edgesFull--;
                }
            }
        }
    } while(referenceGraph.verticesAmount() * 2 > referenceGraph.MSTPrim()->edgesAmount() + 2);
    return graph;
}

GraphPointer GraphGenerator::generateGraphUndirected(FactoryPointer factory,
                                                     size_t vertices,
                                                     unsigned char fulfilment) {
    GraphPointer graph;
    ListGraph referenceGraph(0);
    do {
        referenceGraph = ListGraph(vertices);
        graph = factory->build(vertices);
        unsigned long edgesFull = fullGraphEdgesUndirected(vertices);
        unsigned long edgesInGraph = edgesFull * fulfilment / 100;
        for(size_t i = 0; i < vertices; i++) {
            for(size_t k = i + 1; k < vertices; k++) {
                if(randomizer.getBool(edgesInGraph, edgesFull)) {
                    graph->addEdgeUndirected(i, k, randomizer.getInt(50));
                    referenceGraph.addEdgeUndirected(i, k, randomizer.getInt(50));
                    edgesInGraph--;
                }
                edgesFull--;
            }
        }
    } while(referenceGraph.verticesAmount() * 2 > referenceGraph.MSTPrim()->edgesAmount() + 2);
    return graph;






/*    auto graph = factory->build(vertices);
    unsigned long edgesFull = fullGraphEdgesUndirected(vertices);
    unsigned long edgesInGraph = edgesFull * fulfilment / 100;
    for(size_t i = 0; i < vertices; i++) {
        for(size_t k = i + 1; k < vertices; k++) {
            if(randomizer.getBool(edgesInGraph, edgesFull)) {
                graph->addEdgeDirected(i, k, randomizer.getInt(50));
                edgesInGraph--;
            }
            edgesFull--;
        }
    }
    return graph;*/
}

GraphPointer GraphGenerator::buildGraphDirected(FactoryPointer factory, const std::shared_ptr<int32_t[]>& elements) {
    auto graph = factory->build(elements[1]);
    for(int i = 2; i < 2 + elements[0] * 3; i += 3) {
        graph->addEdgeDirected(elements[i], elements[i + 1], elements[i + 2]);
    }
    return graph;
}

GraphPointer GraphGenerator::buildGraphUndirected(FactoryPointer factory, const std::shared_ptr<int32_t[]>& elements) {
    auto graph = factory->build(elements[1]);
    for(int i = 2; i < 2 + elements[0] * 3; i += 3) {
        graph->addEdgeUndirected(elements[i], elements[i + 1], elements[i + 2]);
    }
    return graph;
}

unsigned long GraphGenerator::fullGraphEdgesUndirected(size_t vertices) {
    return fullGraphEdgesDirected(vertices) / 2;
}

unsigned long GraphGenerator::fullGraphEdgesDirected(size_t vertices) {
    return vertices * (vertices - 1);
}

Array<GraphPointer>
GraphGenerator::generateDirectedTwin(Array<FactoryPointer> factories, size_t vertices, unsigned char fulfilment) {
    ListGraph referenceGraph(0);
    Array<GraphPointer> graphs(factories.getLength());
    for(int i = 0; i < factories.getLength(); i++) {
        graphs[i] = factories[i]->build(vertices);
    }
    do {
        unsigned long edgesFull = fullGraphEdgesDirected(vertices);
        unsigned long edgesInGraph = edgesFull * fulfilment / 100;
        for(size_t i = 0; i < vertices; i++) {
            for(size_t k = 0; k < vertices; k++) {
                if(i != k) {
                    if(randomizer.getBool(edgesInGraph, edgesFull)) {
                        auto weight = randomizer.getInt(50);
                        referenceGraph.addEdgeDirected(i, k, weight);
                        for(int j = 0; j < graphs.getLength(); j++) {
                            graphs[j]->addEdgeDirected(i, k, weight);
                        }
                        edgesInGraph--;
                    }
                    edgesFull--;
                }
            }
        }
    } while(referenceGraph.verticesAmount() * 2 > referenceGraph.MSTPrim()->edgesAmount() + 2);
    return graphs;
}

Array<GraphPointer>
GraphGenerator::generateUndirectedTwin(Array<FactoryPointer> factories, size_t vertices, unsigned char fulfilment) {
    ListGraph referenceGraph(0);
    Array<GraphPointer> graphs(factories.getLength());
    for(int i = 0; i < factories.getLength(); i++) {
        graphs[i] = factories[i]->build(vertices);
    }
    do {
        unsigned long edgesFull = fullGraphEdgesDirected(vertices);
        unsigned long edgesInGraph = edgesFull * fulfilment / 100;
        for(size_t i = 0; i < vertices; i++) {
            for(size_t k = i + 1; k < vertices; k++) {
                if(randomizer.getBool(edgesInGraph, edgesFull)) {
                    auto weight = randomizer.getInt(50);
                    referenceGraph.addEdgeUndirected(i, k, weight);
                    for(int j = 0; j < graphs.getLength(); j++) {
                        graphs[j]->addEdgeUndirected(i, k, weight);
                    }
                    edgesInGraph--;
                }
                edgesFull--;
            }
        }
    } while(referenceGraph.verticesAmount() * 2 > referenceGraph.MSTPrim()->edgesAmount() + 2);
    return graphs;
}
