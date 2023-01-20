#include <map>
#include "array_sequence.hpp"
#include "dictionary.hpp"

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

template <typename Tweight>
class Path {
public:
	ArraySequence<Edge<Tweight> > path;
	int add_edge(Edge<Tweight> a) {
		if (path.GetLength() > 0 && path.GetLast().to_id != a.from_id && path.GetLast().to_id != a.to_id) {
			return -1;
		}
		path.Append(a);
		return 0;
	}
};
template <class Tweight>
std::ostream& operator<< (std::ostream& out, Path<Tweight>& a) {
	for (int i = 0; i < a.path.GetLength(); ++i) {
		auto b = a.path.Get(i);
		cout << b.from_id << " " << b.to_id << " " << b.weight;
	}
	return out;
}

template<typename Tweight>
class Graph {
private:
	IDict<int, Edge<Tweight> > edges;
	ArraySequence<Node> nodes;
	int id_node = 0, id_edge = 0;

public:
	Graph(const int& size) {
		for (int i = 0; i < size; ++i) {
			nodes.Append(id_node++);
		}
	}

	Graph(const Graph& other) : edges(other.edges), nodes(other.nodes) {}

	ArraySequence<Edge<Tweight> > Get_edges() {
		return this->edges;
	}

	ArraySequence<Node> Get_nodes() {
		return this->nodes;
	}

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
		edges.add(id_edge - 1, edge);
		for (int i = 0; i < this->nodes.GetLength(); ++i) {
			if (this->nodes.Get(i).id == from) {
				ArraySequence<int> *buf = this->nodes.Get(i).node_edges;
				buf->Append(edge.id);
			}
			if (this->nodes.Get(i).id == to) {
				ArraySequence<int> *buf = this->nodes.Get(i).node_edges;
				buf->Append(edge.id);
			}
		}
		return 0;
	}
	
	Pair<ArraySequence<Tweight>, ArraySequence<Pair<int, int> > > Dijkstra(int ver) {
		ArraySequence<Tweight> dist;
		ArraySequence<Pair<int, int> > parent;  //id node - id edge
		Pair<int, int> buf(-1, -1);
		for (int i = 0; i < this->id_node; ++i) {
			dist.Append(NMAX);
			parent.Append(buf);
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
				if (!(used.Get(i)) && (curr_ver == -1 || dist.Get(i) < dist.Get(curr_ver))) {
					curr_ver = i;
				}
			}

			if (curr_ver == -1) {
				break;
			}

			used.Set(true, curr_ver);
			for (int i = 0; i < this->nodes.Get(curr_ver).node_edges->GetLength(); ++i) {
				int first = this->edges.get(this->nodes.Get(curr_ver).node_edges->Get(i)).from_id;
				int second = this->edges.get(this->nodes.Get(curr_ver).node_edges->Get(i)).to_id;
				Tweight weight_ = this->edges.get(this->nodes.Get(curr_ver).node_edges->Get(i)).weight;
				if (first != curr_ver) {
					if (dist.Get(first) > dist.Get(curr_ver) + weight_) {
						dist.Set(dist.Get(curr_ver) + weight_, first);
						Pair<int, int> buf(curr_ver, this->nodes.Get(curr_ver).node_edges->Get(i));
						parent.Set(buf, first);
					}
				}
				else {
					if (dist.Get(second) > dist.Get(curr_ver) + weight_) {
						dist.Set(dist.Get(curr_ver) + weight_, second);
						Pair<int, int> buf(curr_ver, this->nodes.Get(curr_ver).node_edges->Get(i));
						parent.Set(buf, second);
					}
				}
			}
		}
		Pair<ArraySequence<Tweight>, ArraySequence<Pair<int, int> > > ans(dist, parent);
		return ans;
	}

	Pair<Tweight, Path<Tweight> > find_dist(int from, int to) {
		Pair<ArraySequence<Tweight>, ArraySequence<Pair<int, int> > > ans = Dijkstra(from);
		Path<Tweight> path;
		ArraySequence<Pair<int, int> > parent = ans.value;
		int curr_id = to;
		while (curr_id != -1) {
			path.add_edge(edges.get(parent.Get(curr_id).value));
			curr_id = parent.Get(curr_id).key;
		}

		if (ans.key.Get(to) == NMAX) {
			Pair<Tweight, Path<Tweight> > res(-1, path);
			return res;
		}
		Pair<Tweight, Path<Tweight> > res(ans.key.Get(to), path);
		return res;
	}

	ArraySequence<Tweight> find_dist_to_all(int from) {Dijkstra(from);
		Pair<ArraySequence<Tweight>, ArraySequence<Pair<int, int> > > ans = Dijkstra(from);
		return ans.key;
	}

	void dfs(int vertex, ArraySequence<int>& comp, ArraySequence<bool>& used) {
		used.Set(true, vertex);
		comp.Append(vertex);
		for (int i = 0; i < this->nodes.Get(vertex).node_edges->GetLength(); ++i) {
			int first = this->edges.get(this->nodes.Get(vertex).node_edges->Get(i)).from_id;
			int second = this->edges.get(this->nodes.Get(vertex).node_edges->Get(i)).to_id;
			if (first != vertex) {
				if (!used.Get(first)) {
					dfs(first, comp, used);
				}
			}
			else {
				if (!used.Get(second)) {
					dfs(second, comp, used);
				}
			}
		}
	}

	ArraySequence<ArraySequence<int> > find_connectivity_component() {
		ArraySequence<bool> used;
		ArraySequence<ArraySequence<int> > ans;
		for (int i = 0; i < this->id_node; ++i) {
			used.Append(false);
		}
		for (int i = 0; i < this->id_node; ++i) {
			if (!used.Get(i)) {
				ArraySequence<int> comp;
				dfs(i, comp, used);
				ans.Append(comp);
			}
		}

		return ans;
	}


	int delete_edge(int id) {
		if (id < 0 || id >id_edge) {
			return -1;
		}
		if (edges.find(id)) {
			edges.delet(id);
			for (int i = 0; i < nodes.GetLength(); ++i) {
				for (int j = 0; j < nodes.Get(i).node_edges->GetLength(); ++j) {
					if (nodes.Get(i).node_edges->Get(j) == id) {
						nodes.Get(i).node_edges->remove(id);
					}
				}
			}
			return 0;
		}
		return -1;
	}
	~Graph() {
	}
};
