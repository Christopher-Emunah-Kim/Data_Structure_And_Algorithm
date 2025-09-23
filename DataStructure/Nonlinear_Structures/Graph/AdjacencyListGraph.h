#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

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


//그래프 구조체
struct AdjacencyListGraph
{
public:
	AdjacencyListGraph(int n)
	{
		data = std::vector<std::vector<std::pair<int, int>>>(n, std::vector<std::pair<int, int>>());
	}

	void AddEdge(const city from, const city to, int dis)
	{
		std::cout << "AddEdge : " << from << " -> " << to << " (" << dis << "km)" << std::endl;

		auto n1 = static_cast<int>(from);
		auto n2 = static_cast<int>(to);

		data[n1].push_back(std::make_pair(n2, dis));
		data[n2].push_back(std::make_pair(n1, dis));
	}

	void RemoveEdge(const city from, const city to)
	{
		std::cout << "RemoveEdge : " << from << " -> " << to << std::endl;

		auto n1 = static_cast<int>(from);
		auto n2 = static_cast<int>(to);

		std::remove_if(data[n1].begin(), data[n1].end(),
			[n2](const std::pair<int, int>& edge) { return edge.first == n2; });
		std::remove_if(data[n2].begin(), data[n2].end(),
			[n1](const std::pair<int, int>& edge) { return edge.first == n1; });
		
	}

private:
	std::vector<std::vector<std::pair<int, int>>> data;
};


//테스트 코드
//int main()
//{
//	AdjacencyListGraph graph(6);
//	graph.AddEdge(city::MOSCOW, city::LONDON, 2500);
//	graph.AddEdge(city::MOSCOW, city::SEOUL, 7000);
//	graph.AddEdge(city::MOSCOW, city::SEATTLE, 7500);
//	graph.AddEdge(city::LONDON, city::DUBAI, 5500);
//	graph.AddEdge(city::LONDON, city::SEATTLE, 7200);
//	graph.AddEdge(city::SEOUL, city::SYDNEY, 7800);
//	graph.RemoveEdge(city::MOSCOW, city::SEOUL);
//
//	return 0;
//}