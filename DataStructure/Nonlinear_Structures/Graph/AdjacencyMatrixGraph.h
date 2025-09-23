#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

enum class city : uint8_t
{
	MOSCOW,
	LONDON,
	SEOUL,
	SEATTLE,
	DUBAI,
	SYDNEY
};


std::ostream& operator<<(std::ostream& os, const city& city)
{
	switch (city)
	{
	case city::MOSCOW:
		os << "Moscow";
		break;
	case city::LONDON:
		os << "London";
		break;
	case city::SEOUL:
		os << "Seoul";
		break;
	case city::SEATTLE:
		os << "Seattle";
		break;
	case city::DUBAI:
		os << "Dubai";
		break;
	case city::SYDNEY:
		os << "Sydney";
		break;
	default:
		os << "Unknown City";
		break;
	}
	return os;
}

struct AdjacencyMatrixGraph
{
public:
	AdjacencyMatrixGraph(int n)
	{
		data.reserve(n);
		std::vector<int> row(n);
		std::fill(row.begin(), row.end(), -1);

		for(int i = 0; i < n; i++)
			data.push_back(row);
	}

	void AddEdge(const city from, const city to, int dis)
	{
		std::cout << "AddEdge " << from << " to " << to << " : " << dis << std::endl;

		auto n1 = static_cast<int>(from);
		auto n2 = static_cast<int>(to);
		
		data[n1][n2] = dis;
		data[n2][n1] = dis; //무향 그래프
	}

	void RemoveEdge(const city from, const city to)
	{
		std::cout << "RemoveEdge " << from << " to " << to << std::endl;

		auto n1 = static_cast<int>(from);
		auto n2 = static_cast<int>(to);

		data[n1][n2] = -1;
		data[n2][n1] = -1; //무향 그래프
	}

private:
	std::vector<std::vector<int>> data;
};

//int main()
//{
//	AdjacencyMatrixGraph graph(6);
//	graph.AddEdge(city::MOSCOW, city::LONDON, 2500);
//	graph.AddEdge(city::MOSCOW, city::SEOUL, 6600);
//	graph.AddEdge(city::LONDON, city::SEATTLE, 7200);
//	graph.AddEdge(city::LONDON, city::DUBAI, 5500);
//	graph.AddEdge(city::SEOUL, city::SYDNEY, 7800);
//	graph.AddEdge(city::SEATTLE, city::DUBAI, 12000);
//	graph.AddEdge(city::DUBAI, city::SYDNEY, 12000);
//	graph.RemoveEdge(city::DUBAI, city::SYDNEY);
//
//	return 0;
//}