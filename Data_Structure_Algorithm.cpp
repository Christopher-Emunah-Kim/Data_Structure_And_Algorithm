
#include <iostream>
#include <string>
#include "DataStructure/Nonlinear_Structures/Graph/AdjacencyListGraph.h"

using namespace std;

int main()
{
	AdjacencyListGraph graph(6);
	graph.AddEdge(city::MOSCOW, city::LONDON, 2500);
	graph.AddEdge(city::MOSCOW, city::SEOUL, 7000);
	graph.AddEdge(city::MOSCOW, city::SEATTLE, 7500);
	graph.AddEdge(city::LONDON, city::DUBAI, 5500);
	graph.AddEdge(city::LONDON, city::SEATTLE, 7200);
	graph.AddEdge(city::SEOUL, city::SYDNEY, 7800);
	graph.RemoveEdge(city::MOSCOW, city::SEOUL);

	return 0;
}