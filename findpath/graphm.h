#include "nodedata.h"
class GraphM {                            
   public:
       GraphM();
         void buildGraph(istream&); 
         bool insertEdge(int,int,int);
         bool removeEdge(int,int);
         void findShortestPath();
         void displayAll() const;
         void display(int,int) const;
         
       


   private:
        struct TableType {
           bool visited;          // whether node has been visited
           int dist;              // shortest distance from source known so far
           int path;              // previous node in path of min dist
        };
        NodeData data[101];              // data for graph nodes 
        int C[101][101];            // Cost array, the adjacency matrix
        int size;                             // number of nodes in the graph
        TableType T[101][101];      // stores visited, distance, path
        void pathdisplay(int, int) const;
        void datadisplay(int, int) const;
   
   };

