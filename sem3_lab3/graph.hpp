#include <map>
#include "array_sequence.hpp"

const int NMAX = 100000000;
using std::cout;

template<typename Tweight>
struct Edge {
public:
	int id;
	Tweight weight;
	int from_id;
	int to_id;

	Edge() {
		id = -1;
	}
	Edge(int id_) {
		id = id_;
		weight = 0;
		from_id = -1;
		to_id = -1;
	}

	Edge(int id_, int from, int to, Tweight weight_) : id(id_), from_id(from), to_id(to), weight(weight_) {}
};


struct Node {
public:
	int id;
	ArraySequence<int> *node_edges;
	Node() {
		id = -1;
		node_edges = new ArraySequence<int>();
	}
	Node(int id_) {
		id = id_;
		node_edges = new ArraySequence<int>();
	}

	Node(int id_, ArraySequence<int>* k) {
		id = id_;
		node_edges = k;
	}
};


template<typename Tweight>
class Graph {
public:
	ArraySequence<Edge<Tweight> > edges;
	ArraySequence<Node> nodes;
	int id_node = 0, id_edge = 0;
public:
	 
	Graph(const int& size) {
		for (int i = 0; i < size; ++i) {
			nodes.Append(id_node++);
		}
	}

	Graph(const Graph& other) : edges(other.edges), nodes(other.nodes) {}

	void Add_node() {
		Node node(id_node++);
		nodes.Append(node);
	}

	void Add_node(const Node& node) {
		nodes.Append(node);
	}

	int Add_edge(int from, int to, Tweight weight_) {
		if (from > id_node || to > id_node) {
			return -1;
		}
		Edge<Tweight> edge(id_edge++, from, to, weight_);
		edges.Append(edge);
		for (int i = 0; i < this->nodes.GetLength(); ++i) {
			if (this->nodes.Get(i).id == from) {
				ArraySequence<int> *buf = this->nodes.Get(i).node_edges;
				buf->Append(edge.id);
				//Node new_node(this->nodes.Get(i).id, buf);
				//this->nodes.Set(new_node, i);
			}
			if (this->nodes.Get(i).id == to) {
				ArraySequence<int> *buf = this->nodes.Get(i).node_edges;
				buf->Append(edge.id);
				//Node new_node(this->nodes.Get(i).id, buf);
				//this->nodes.Set(new_node, i);
			}
		}
		return 0;
	}
	
	ArraySequence<Tweight> Dijkstra(int ver) {
		ArraySequence<Tweight> dist;
		for (int i = 0; i < this->id_node; ++i) {
			dist.Append(NMAX);
		}
		dist.Set(0, ver);
		ArraySequence<bool> used;
		for (int i = 0; i < this->id_node; ++i) {
			used.Append(false);
		}

		int curr_ver = 0;
		while (curr_ver != -1) {
			curr_ver = -1;
			for (int i = 0; i < this->id_node; ++i) {
				if (!used.Get(i) && (curr_ver != -1 || dist.Get(i) < dist.Get(curr_ver))) {
					curr_ver = i;
				}
			}

			if (curr_ver == -1) {
				break;
			}

			used.Set(true, curr_ver);
			for (int i = 0; i < this->nodes.Get(curr_ver).node_edges->GetLength(); ++i) {
				int first = this->edges.Get(this->nodes.Get(curr_ver).node_edges->Get(i)).from_id;
				int second = this->edges.Get(this->nodes.Get(curr_ver).node_edges->Get(i)).to_id;
				Tweight weight_ = this->edges.Get(this->nodes.Get(curr_ver).node_edges->Get(i)).weight;
				if (first != curr_ver) {
					if (dist.Get(first) > dist.Get(curr_ver) + weight_) {
						dist.Set(dist.Get(curr_ver) + weight_, first);
					}
				}
				else {
					if (dist.Get(second) > dist.Get(curr_ver) + weight_) {
						dist.Set(dist.Get(curr_ver) + weight_, second);
					}
				}
			}

			for (int i = 0; i < 5; ++i) {
				cout << dist.Get(i) << " ";
			}
			cout << "\n";
		}

		return dist;
	}

	Tweight find_dist(int from, int to) {
		ArraySequence<Tweight> ans = Dijkstra(from);
		return (ans.Get(to) == NMAX ? -1 : ans.Get(to));
	}
};
