#ifndef SDIZO2_GRAPHGENERATOR_H
#define SDIZO2_GRAPHGENERATOR_H

#include "Graph.h"
#include "GraphFactory.h"
#include "../program/Randomizer.h"
#include "../structure_templates_lib/structures.h"
#include "../graphs/ListGraph.h"

class GraphGenerator {
public:
    GraphPointer generateGraphDirected(FactoryPointer factory, size_t vertices, unsigned char fulfilment);
    GraphPointer generateGraphUndirected(FactoryPointer factory, size_t vertices, unsigned char fulfilment);
    GraphPointer buildGraphDirected(FactoryPointer factory, const std::shared_ptr<int32_t[]>&);
    GraphPointer buildGraphUndirected(FactoryPointer factory, const std::shared_ptr<int32_t[]>&);
    Array<GraphPointer> generateDirectedTwin(Array<FactoryPointer> factories, size_t vertices, unsigned char fulfilment);
    Array<GraphPointer> generateUndirectedTwin(Array<FactoryPointer> factories, size_t vertices, unsigned char fulfilment);

private:
    static unsigned long fullGraphEdgesUndirected(size_t vertices);
    static unsigned long fullGraphEdgesDirected(size_t vertices);

    Randomizer randomizer;
};


#endif //SDIZO2_GRAPHGENERATOR_H
