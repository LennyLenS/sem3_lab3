#include <iostream>
#include "graph.hpp"

using namespace std;

int main() {
	Graph<int> gr(5);
	gr.Add_edge(1, 2, 4);
	gr.Add_edge(1, 3, 10);
	gr.Add_edge(1, 4, 6);
	gr.Add_edge(2, 3, 5);
	gr.Add_edge(4, 3, 7);
	cout << gr.find_dist(1, 3);
}