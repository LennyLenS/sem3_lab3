#include <iostream>
#include <regex>
#include <fstream>
#include "graph.hpp"
#include "dictionary.hpp"

using namespace std;

typedef struct parametrs {
	bool help = false;
	bool quit = false;
	bool run = false;
	bool error = false;
	bool dist_one = false;
	bool dist_all = false;
	bool compon = false;
	bool console = false;
	int vertex = 0;
	int vertex2 = 0;
	string data = "";
	bool file = false;
	bool out_file = false;
	string file_name = "test.txt";
	string out_file_name = "out_test.txt";
}parametrs;

parametrs parsing(string s) {
	parametrs buf;
	static const regex r("^(help|((run|test){1}\\s*-(d_o|d_a|c){1}\\s*(\\d+)?\\s*(\\d+)?\\s*(-console)?\\s*(-fi\\s*(\\S*))?\\s*(-fo\\s*(\\S*))?)|quit)$");
	smatch mat;
	if (regex_search(s, mat, r)) {
		/*
		for (int i = 0; i < mat.length(); ++i) {
			cout << i << " " << mat[i].str() << "\n";
		}
		*/
		if (s.find("help") != -1) {
			buf.help = true;
		}
		if (s.find("d_o") != -1) {
			buf.dist_one = true;
			if (mat[5].str() != "") {
				buf.vertex = stoi(mat[5].str());
			}
			if (mat[6].str() != "") {
				buf.vertex2 = stoi(mat[6].str());
			}
		}
		if (s.find("d_a") != -1) {
			buf.dist_all = true;
			if (mat[5].str() != "") {
				buf.vertex = stoi(mat[5].str());
			}
		}
		if (s.find("c") != -1) {
			buf.compon = true;
		}
		if (s.find("-console") != -1) {
			buf.console = true;
		}
		if (s.find("-fi") != -1) {
			buf.file = true;
			if (mat[8].str() != "") {
				buf.file_name = mat[9].str();
			}
		}
		if (s.find("-fo") != -1) {
			buf.out_file = true;
			if (mat[10].str() != "") {
				buf.out_file_name = mat[11].str();
			}
		}
		if (s.find("run") != -1) {
			buf.run = true;
		}

		if (s.find("quit") != -1) {
			buf.quit = true;
		}
	}
	else {
		buf.error = true;
	}

	return buf;
}

void update(parametrs buf) {
	cout << "	run - command for making graph. Possible flags: \n \
		-d_o for find distance between 2 points in the graph \n\
		-d_a for find distance between 1 point and other in the graph \n\
		-c for find component of connectivity \n\
		-fi for reading from file\n \
		-fo for reading from file\n \
quit for finish programme\n";
}

int main() {
	bool quit = false;
	do {
		parametrs buf;
		string s;
		std::getline(cin, s);
		buf = parsing(s);
		if (buf.error) {
			cout << "Error in the request: " << s << "\n";
		}
		else {
			if (buf.run) {
				if (buf.file) {
					bool flag = false;
					int count_ver, count_edg;
					std::ifstream in(buf.file_name);

					if (in.is_open()) {
						in >> count_ver >> count_edg;
						Graph<int> gr(count_ver);
						for (int i = 0; i < count_edg; ++i) {
							int from, to, weight;
							in >> from >> to >> weight;
							if (from < 0 || from >= count_ver || to < 0 || to > count_ver || weight < 0) {
								cout << "Uncorrect data!!";
								flag = true;
								break;
							}
							gr.Add_edge(from, to, weight);
						}
						if (!flag) {
							std::ofstream out(buf.out_file_name);
							if (buf.compon) {
								auto a = gr.find_connectivity_component();
								if (buf.out_file && out.is_open()) {
									for (int i = 0; i < a.GetLength(); ++i) {
										auto b = a.Get(i);
										out << "Component " << i << "\n";
										out << b << "\n";
									}
								}
								else {
									for (int i = 0; i < a.GetLength(); ++i) {
										auto b = a.Get(i);
										cout << "Component " << i << "\n";
										cout << b << "\n";
									}
								}
							}
							if (buf.dist_one) {
								auto a = gr.find_dist(buf.vertex, buf.vertex2);
								if (buf.out_file && out.is_open()) {
									out << a.key << "\n";
									for (int i = a.value.Get_path().GetLength() - 1; i >= 0; --i) {
										Edge<int> curr_edge = a.value.Get_path().Get(i);
										out << curr_edge.from_id << " " << curr_edge.to_id << " " << curr_edge.weight << "\n";
									}
								}
								else {
									cout << a.key << "\n";
									for (int i = a.value.Get_path().GetLength() - 1; i >= 0; --i) {
										Edge<int> curr_edge = a.value.Get_path().Get(i);
										cout << curr_edge.from_id << " " << curr_edge.to_id << " " << curr_edge.weight << "\n";
									}
								}
							}
							if (buf.dist_all) {
								auto a = gr.find_dist_to_all(buf.vertex);
								if (buf.out_file && out.is_open()) {
									out << a << "\n";
								}
								else {
									cout << a << "\n";
								}
							}
						}
					}
					else {
						cout << "Cant open file!\n";
					}
				}
				else {
					bool flag = false;
					int ver, edg;
					cin >> ver >> edg;
					Graph<int> gr(ver);
					for (int i = 0; i < edg; ++i) {
						int from, to, weight;
						cout << "Edge " << i << ": ";
						cin >> from >> to >> weight;
						if (from < 0 || from >= ver || to < 0 || to > ver || weight < 0) {
							cout << "Uncorrect data!!";
							flag = true;
							break;
						}
						gr.Add_edge(from, to, weight);
					}
					getline(cin, s);
					if (!flag) {
						std::ofstream out(buf.out_file_name);
						if (buf.compon) {
							auto a = gr.find_connectivity_component();
							if (buf.out_file && out.is_open()) {
								for (int i = 0; i < a.GetLength(); ++i) {
									auto b = a.Get(i);
									out << "Component " << i << "\n";
									out << b << "\n";
								}
							}
							else {
								for (int i = 0; i < a.GetLength(); ++i) {
									auto b = a.Get(i);
									cout << "Component " << i << "\n";
									cout << b << "\n";
								}
							}
						}
						if (buf.dist_one) {
							auto a = gr.find_dist(buf.vertex, buf.vertex2);
							if (buf.out_file && out.is_open()) {
								out << a.key << "\n";
								for (int i = a.value.Get_path().GetLength() - 1; i >= 0; --i) {
									Edge<int> curr_edge = a.value.Get_path().Get(i);
									out << curr_edge.from_id << " " << curr_edge.to_id << " " << curr_edge.weight << "\n";
								}
							}
							else {
								cout << a.key << "\n";
								for (int i = a.value.Get_path().GetLength() - 1; i >= 0; --i) {
									Edge<int> curr_edge = a.value.Get_path().Get(i);
									cout << curr_edge.from_id << " " << curr_edge.to_id << " " << curr_edge.weight << "\n";
								}
							}
						}
						if (buf.dist_all) {
							auto a = gr.find_dist_to_all(buf.vertex);
							if (buf.out_file && out.is_open()) {
								out << a << "\n";
							}
							else {
								cout << a << "\n";
							}
						}
					}
				}
			}
			else if (buf.help) {
				update(buf);
			}
		}
		quit = buf.quit;
		//getline(cin, s);
	} while (!quit);

	return 0;
}