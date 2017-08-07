#include "Graph.h"

int main()
{   
	{
		Graph<int> graph("graph.txt");
		std::cout << graph.GetVertexNumbers() << '\n';
		std::cout << graph.GetEdgeNumbers() << "\n";
		std::cout << Graph<int>::GetDegree(graph,0) << '\n';
		std::cout << Graph<int>::GetMaxDegree(graph) << '\n';
		std::cout << Graph<int>::GetMinDegree(graph) << '\n';
		std::cout << Graph<int>::GetAvergeDegree(graph) << '\n';
		std::cout << Graph<int>::GetNumberOfSelfLoops(graph) << '\n';
	}
	system("pause");
	return 0;
}