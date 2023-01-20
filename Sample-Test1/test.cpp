#include "pch.h"
#include "../sem3_lab3/graph.hpp"

TEST(NodeTest, Node_test1) {
	Node node;
	int id_ = node.id;
	ASSERT_EQ(id_, -1);
}

TEST(NodeTest, Node_test2) {
	Node node(4);
	int id_ = node.id;
	ASSERT_EQ(id_, 4);
	ASSERT_EQ(node.node_edges->GetLength(), 0);
}

TEST(NodeTest, Node_test3) {
	Node node(10);
	int id_ = node.id;
	ASSERT_EQ(id_, 10);
	ASSERT_EQ(node.node_edges->GetLength(), 0);
}

TEST(NodeTest, Node_test4) {
	ArraySequence<int>* buf = new ArraySequence<int>;
	buf->Append(1);
	buf->Append(3);
	Node node(14, buf);
	int id_ = node.id;
	ASSERT_EQ(id_, 14);
	ASSERT_EQ(node.node_edges->GetLength(), 2);
	ASSERT_EQ(node.node_edges->Get(0), 1);
	ASSERT_EQ(node.node_edges->Get(1), 3);
}


TEST(EdgeTest, Edge_test1) {
	Edge<int> edge;
	int id_ = edge.id;
	ASSERT_EQ(id_, -1);
}

TEST(EdgeTest, Edge_test2) {
	Edge<int> edge(4);
	int id_ = edge.id;
	ASSERT_EQ(id_, 4);
	ASSERT_EQ(edge.weight, 0);
}

TEST(EdgeTest, Edge_test3) {
	Edge<int> edge(4);
	int id_ = edge.id;
	ASSERT_EQ(id_, 4);
	ASSERT_EQ(edge.weight, 0);
	ASSERT_EQ(edge.from_id, -1);
	ASSERT_EQ(edge.to_id, -1);
}

TEST(EdgeTest, Edge_test4) {
	Edge<int> edge(4, 3, 6, 10);
	int id_ = edge.id;
	ASSERT_EQ(id_, 4);
	ASSERT_EQ(edge.weight, 10);
	ASSERT_EQ(edge.from_id, 3);
	ASSERT_EQ(edge.to_id, 6);
}

TEST(EdgeTest, Edge_test5) {
	Edge<int> edge(7, 4, 1, 6);
	int id_ = edge.id;
	ASSERT_EQ(id_, 7);
	ASSERT_EQ(edge.weight, 6);
	ASSERT_EQ(edge.from_id, 4);
	ASSERT_EQ(edge.to_id, 1);
}

TEST(GraphTest, Graph_test1) {
	Graph<int> gr(10);
	ASSERT_EQ(gr.Get_nodes().GetLength(), 10);
}

TEST(GraphTest, Graph_test2) {
	Graph<int> gr(10);
	gr.Add_edge(0, 1, 6);
	ASSERT_EQ(gr.Get_edges().GetLength(), 1);
	ASSERT_EQ(gr.Get_edges().Get(0).from_id, 0);
	ASSERT_EQ(gr.Get_edges().Get(0).to_id, 1);
	ASSERT_EQ(gr.Get_edges().Get(0).weight, 6);
}

TEST(GraphTest, Graph_test3) {
	Graph<int> gr(10);
	gr.Add_edge(0, 1, 6);
	gr.Add_edge(3, 6, 13);
	ASSERT_EQ(gr.Get_edges().GetLength(), 2);
	ASSERT_EQ(gr.Get_edges().Get(1).from_id, 3);
	ASSERT_EQ(gr.Get_edges().Get(1).to_id, 6);
	ASSERT_EQ(gr.Get_edges().Get(1).weight, 13);
}

TEST(GraphTest, Graph_test4) {
	Graph<int> gr(10);
	gr.Add_edge(0, 1, 6);
	gr.Add_edge(3, 6, 13);
	gr.Add_edge(5, 3, 18);
	ASSERT_EQ(gr.Get_edges().GetLength(), 3);
	ASSERT_EQ(gr.find_connectivity_component().GetLength(), 7);
}

TEST(GraphTest, Graph_test5) {
	Graph<int> gr(8);
	gr.Add_edge(0, 1, 6);
	gr.Add_edge(3, 6, 13);
	gr.Add_edge(5, 3, 18);
	gr.Add_edge(2, 3, 5);
	gr.Add_edge(5, 6, 2);
	ASSERT_EQ(gr.Get_edges().GetLength(), 5);
	ASSERT_EQ(gr.find_connectivity_component().GetLength(), 4);
	ASSERT_EQ(gr.find_dist(2, 6), 18);
}

TEST(GraphTest, Graph_test6) {
	Graph<int> gr(8);
	gr.Add_edge(0, 1, 6);
	gr.Add_edge(3, 6, 13);
	gr.Add_edge(5, 3, 10);
	gr.Add_edge(2, 3, 5);
	gr.Add_edge(5, 6, 2);
	ASSERT_EQ(gr.Get_edges().GetLength(), 5);
	ASSERT_EQ(gr.find_connectivity_component().GetLength(), 4);
	ASSERT_EQ(gr.find_dist(2, 6), 17);
}

TEST(GraphTest, Graph_test7) {
	Graph<int> gr(8);
	gr.Add_edge(0, 1, 6);
	gr.Add_edge(3, 6, 13);
	gr.Add_edge(5, 3, 11);
	gr.Add_edge(2, 3, 5);
	gr.Add_edge(5, 6, 2);
	ASSERT_EQ(gr.Get_edges().GetLength(), 5);
	ASSERT_EQ(gr.find_connectivity_component().GetLength(), 4);
	ASSERT_EQ(gr.find_dist(2, 6), 18);
}

TEST(GraphTest, Graph_test8) {
	Graph<int> gr(8);
	gr.Add_edge(0, 1, 6);
	gr.Add_edge(3, 6, 13);
	gr.Add_edge(5, 3, 11);
	gr.Add_edge(2, 3, 5);
	gr.Add_edge(5, 6, 2);
	ASSERT_EQ(gr.Get_edges().GetLength(), 5);
	ASSERT_EQ(gr.find_connectivity_component().GetLength(), 4);
	ASSERT_EQ(gr.find_dist(2, 0), -1);
}