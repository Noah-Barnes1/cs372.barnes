#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include "Tree.hpp"
#include "avltree.hpp"
#include <cmake>

int main() {
	std::vector<int> sizes = { 100,500,1000,2500,5000,10000 };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Elements\tBS avg (us)\tAVL avg \n";
	for (int n : sizes) {
		Tree<int> bst;
		AVLTree<int avl;
		std::uniform_int_distribution<int> valueDist(0, n * 10 + 1000);
		for (int i = 0; i < n; ++i) {
			int v = valueDist(gen);
			bst = bst.insert(v);
			avl.insert(v);
		}
		const std::pair<double, double>& times = measure_search_times(bst, avl, 100);
		std::cout << n << "\t\t" << times.first << "\t\t" << times.second << "\n";
	}
	return 0;
}