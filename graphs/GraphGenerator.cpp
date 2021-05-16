#include "GraphGenerator.h"

GraphPointer GraphGenerator::generateGraphDirected(const FactoryPointer factory, const size_t vertices, const unsigned char fulfilment) {
    auto graph = factory->build(vertices);
    unsigned long edgesFull = fullGraphEdgesDirected(vertices);
    unsigned long edgesInGraph = edgesFull * fulfilment / 100;
    for(size_t i = 0; i < vertices; i++) {
        for(size_t k = 0; k < vertices; k++) {
            if(i != k) {
                if(randomizer.getBool(edgesInGraph, edgesFull)) {
                    graph->addEdgeDirected(i, k, randomizer.getInt(50));
                    edgesInGraph--;
                }
                edgesFull--;
            }
        }
    }
    return graph;
}

GraphPointer
GraphGenerator::generateGraphUndirected(FactoryPointer factory, size_t vertices, unsigned char fulfilment) {
    auto graph = factory->build(vertices);
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
    return graph;
}

GraphPointer GraphGenerator::buildGraphDirected(FactoryPointer factory, std::unique_ptr<int32_t[]> elements) {
    auto graph = factory->build(elements[1]);
    for(int i = 2; i < 2 + elements[0] * 3; i += 3) {
        graph->addEdgeDirected(elements[i], elements[i + 1], elements[i + 2]);
    }
    return graph;
}

GraphPointer GraphGenerator::buildGraphUndirected(FactoryPointer factory, std::unique_ptr<int32_t[]> elements) {
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
