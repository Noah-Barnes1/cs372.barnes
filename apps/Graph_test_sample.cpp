#include <iostream>
#include <vector>
#include <cassert>
#include "AdjListGraph.hpp"
#include "GraphUtils.h"

int main() {
	using G = AdjListGraph<int>;
	std::vector<int> nodes = { 1,2,3,4 };
	std::vector<std::pair<int, int>> edges = {
		{1,2}, {2,3}, {3,1},
		{3,4}, {4,1} 
	};
	G g(nodes, edges);
	assert(isSimpleCycle(g, std::vector<int>{1, 2, 3, 1}) == true);
	assert(isSimpleCycle(g, std::vector<int>{1, 2, 3}) == false);
	assert(isSimpleCycle(g, std::vector<int>{1, 2, 4, 1}) == false);
	g.addEdge(3, 2);
	assert(isSimpleCycle(g, std::vector<int>{1, 2, 3, 2, 1}) == false);
	assert(isSimpleCycle(g, std::vector<int>{1, 1}) == false);
	assert(isSimpleCycle(g, std::vector<int>{1, 2, 1}) == false); // only two distinct nodes
	std::cout << "All simple-cycle tests passed.\n";
	return 0;
}