#include "graphm.h"
#include <limits.h>
#include <algorithm> 
#include <iomanip> 

GraphM::GraphM()
{
	this->size = 0;
	
	for (int i = 0; i < 101; i++)
	{
		for (int w = 0; w < 101; w++)
		{
			this->T[i][w].visited = false;
			this->T[i][w].path = 0;
			this->T[i][w].dist = INT_MAX;
			this->C[i][w] = INT_MAX;
		}
	}
	
}
// tested
void GraphM::buildGraph(istream& input)
{
	
	input >> this->size;
	string sizeInString;
	getline(input,  sizeInString);//skip "/n"
	

	string locationData = "";
	for (int i = 1; i <= this->size; i++)
	{
		this->data[i].setData(input) ;
	}
	int startnode = 0, endnode = 0, distance = 0;
	while (input >> startnode >> endnode >> distance)
	{
		if (startnode == 0)
		{
			getline(input, locationData);// when startnode is 0 , get into next line and prepare for next graph 
			break;
		}

		C[startnode][endnode] = distance;
	}
	
}


void GraphM::pathdisplay (int startnode, int endnode) const
{
	
	
	if (T[startnode][endnode].path == INT_MAX)
	{
		return;
	}
	if (startnode == endnode)
	{
		cout << startnode;
		return;
	}

	if (T[startnode][endnode].path != startnode)
	{
		pathdisplay(startnode, T[startnode][endnode].path);
		cout << endnode << " ";
	}
	else 
	{
		cout << endnode << " ";
	}
	
}

void GraphM::datadisplay(int startnode, int endnode) const
{
	if (T[startnode][endnode].path == INT_MAX)
	{
		return;
	}
	if (startnode == endnode)
	{
		cout << startnode;
		return;
	}

	if (T[startnode][endnode].path != startnode)
	{
		datadisplay(startnode, T[startnode][endnode].path);
		cout << data[endnode] << endl;
	}
	else
	{
		cout << data[endnode] << endl;
	}
}



bool GraphM::insertEdge(int startnode, int endnode, int edge)
{
	// insert node must be valid
	if (startnode > size || startnode <1 || endnode > size || endnode < 1 || startnode == endnode)
	{
		return false;
	}
	// insert edge must be valid
	if (edge < 0)
	{
		return false;
	}
	C[startnode][endnode] = edge;
	return true;
}

bool GraphM::removeEdge(int startnode,int endnode)
{
	// insert node must be valid
	if (startnode > size || startnode <1 || endnode > size || endnode < 1 || startnode == endnode)
	{
		return false;
	}
	C[startnode][endnode] = INT_MAX ;
	return true;
}

void GraphM::findShortestPath()
{
	for (int source = 1; source <= this->size; source++) // TableType T 
	{
		 T[source][source].dist = 0;
		 T[source][source].visited = true;

	     // finds the shortest distance from source to all other nodes
		 for (int i = 1; i <= this->size; i++) // matrix index
		 {
			 
			 if (C[source][i] != INT_MAX)
			 {
				 T[source][i].dist = C[source][i];
				 T[source][i].path = source;
			 }
		 }
		 int nextstart = 0; //find v
		 do {
			 nextstart = 0;
			 int shortestdist = INT_MAX;
			 for (int j = 1; j <= this->size; j++)
			 {
				 if (C[source][j] < shortestdist && T[source][j].visited!= true)// update when dist is smaller and unvisited
				 {
					 shortestdist = C[source][j];
					 nextstart = j;// found
				 }
			 }
			 if (nextstart == 0)// quit loop if there is no more nodes unvisited
			 {
				 break;
			 }
			 T[source][nextstart].visited = true;// marked as visited
			 for (int w = 1; w <= size; w++)// for each w adwacent to v
			 {
				 if (C[nextstart][w] < INT_MAX && C[nextstart][w] != 0 && T[source][w].visited != true)// adwacent to nextstart,avoid itself, and not visited
				 {
					 if (T[source][nextstart].dist + C[nextstart][w] < T[source][w].dist)// only update newstart when incoming dist is smaller 
					 {
						 T[source][w].path = nextstart;
					 }
					 T[source][w].dist = min(T[source][w].dist, T[source][nextstart].dist + C[nextstart][w]);
				 }
			 }
		 } while (nextstart != 0);
	}
}



void GraphM::display(int startnode, int endnode) const
{
	if (startnode<0 || startnode>size || endnode<0 || endnode>size)
	{
		cout << setw(10) << startnode << setw(10) << endnode << setw(10) <<"----" << endl;
		cout << endl;
		return;
	}
	if (T[startnode][endnode].dist == INT_MAX)
	{
		cout << setw(10) << startnode << setw(10) << endnode << setw(10) << "----" << endl;
		cout << endl;
		return;
	}
	else
	{
		cout << setw(10) << startnode << setw(10) << endnode << setw(10) << T[startnode][endnode].dist << setw(15);
		cout << startnode << " "; // cout startnode
		pathdisplay(startnode, endnode);// cout the rest
		cout << endl;
		cout << data[startnode] << endl; // cout startnode
		datadisplay(startnode, endnode);// cout the rest
		cout << endl;
	}
}



void GraphM::displayAll() const
{
	cout << "Description" << setw(20) << "From node" << setw(20) << "To node" << setw(20) << "Dijkstra's" << setw(13) << "Path" << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << data[i] << endl;
		for (int j = 1; j <= size; j++)
		{
			if (i != j)
			{
				if (T[i][j].dist < INT_MAX)
				{
					cout << setw(30) << i << setw(20) << j << setw(20) << T[i][j].dist << setw(10) << i << " ";
					pathdisplay(i, j);
					cout << endl;
				}
				else
				{
					cout << setw(30) << i << setw(20) << j << setw(20) << "----" ;
					cout << endl;
				}
				
			}
		}

	}
	cout << endl;
}


