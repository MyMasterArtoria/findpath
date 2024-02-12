#include "nodedata.h"
class GraphL
{
public :
    GraphL();
    ~GraphL();
    void buildGraph(istream&);
    void depthFirstSearch();
    void displayGraph();
private:
    struct EdgeNode {
        int adjGraphNode;  // subscript of the adjacent graph node
        EdgeNode* nextEdge;
    };

    struct GraphNode {    // structs used for simplicity, use classes if desired
        EdgeNode* edgeHead; // head of the list of edges
        NodeData* data;     // data information about each node
        bool visited;
    };
    GraphNode N[101]; // an array stored all graphnodes
    int size; //size of the graph
    void depthFirstSearchHelper(int);
};

