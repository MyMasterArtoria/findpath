#include "graphl.h"
#include <iomanip> 

GraphL::GraphL()
{
	this->size = 0;
	for (int i = 0; i<101; i++ ) 
	{
		this->N[i].visited = false;
		this->N[i].data = nullptr;
		this->N[i].edgeHead = nullptr;
	}
}

GraphL::~GraphL()
{
	if (N[1].data==nullptr)// quit when array has no element
	{
		return;
	}
	for (int i = 1; i <= size; i++)
	{
		N[i].visited = false;
		EdgeNode* curr = N[i].edgeHead;
		while (curr != nullptr)
		{
			N[i].edgeHead = N[i].edgeHead->nextEdge;
			delete curr;
			curr = nullptr;
			curr = N[i].edgeHead;
		}
		delete N[i].data;
		N[i].data = nullptr;
	}
}

void GraphL::buildGraph(istream& input)
{
	input >> this->size;
	string sizeInString;
	getline(input, sizeInString);//skip "/n"


	string locationData = "";
	for (int i = 1; i <= this->size; i++)
	{
		N[i].data->setData(input);
	}
	int startnode = 0, endnode = 0;
	while (input >> startnode >> endnode )
	{
		if (startnode == 0)
		{
			getline(input, locationData);// when startnode is 0 , get into next line and prepare for next graph 
			break;
		}
		if (N[startnode].edgeHead == nullptr) //when head is null(no adjacent node yet)
		{
			EdgeNode* node =new EdgeNode;
			node->adjGraphNode = endnode;
			node->nextEdge = nullptr;
			N[startnode].edgeHead = node;
		}
		else // already has adjcaent node
		{
			EdgeNode* curr = N[startnode].edgeHead;
			while (curr->nextEdge!= nullptr)
			{
				curr = curr->nextEdge; // find last node in the list
			}
			EdgeNode* node = new EdgeNode;
			node->adjGraphNode = endnode;
			node->nextEdge = nullptr;
			curr->nextEdge = node;// add new node after the last node in the list
		}
	}
}

void GraphL::depthFirstSearch()
{
	cout << "Depth-fisrt ordering:" << setw(10);
	for (int i = 1; i <= size; i++)
	{
		if (N[i].visited == false)
		{
			depthFirstSearchHelper(i);
		}
	}
}



void GraphL::depthFirstSearchHelper(int startnode)
{
	cout << startnode << setw(5);
	N[startnode].visited = true;
	EdgeNode* curr = N[startnode].edgeHead;
	while (curr != nullptr)
	{
		if (N[curr->adjGraphNode].visited == false)
		{
			depthFirstSearchHelper(curr->adjGraphNode);
		}
		curr = curr->nextEdge;
	}
}

void GraphL::displayGraph()
{
	cout << "Graph:" << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << "Node " << i << setw(10) << *N[i].data << endl;
		EdgeNode* curr = N[i].edgeHead;
		while (curr != nullptr)
		{
			cout << "  edge " << i << " " << curr->adjGraphNode << endl;
			curr = curr->nextEdge;
		}
	}

}
