#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

class Graph {
private:
	int* V;
	std::vector<std::pair<int, std::pair<int, int>>> E;
	std::vector<std::vector<int>> undirectedE;
	std::vector<std::vector<int>> directedE;
	int number_of_nodes;
public:
	Graph(int nodes);
	void printGraph();
	void createundirE();
	void createdirE();
	void addEdge(int first_node, int second_node, int weight);
	void DFS();
	void BFS();
};

Graph::Graph(int nodes) {
	V = new int[nodes];
	number_of_nodes = nodes;
	for (int i = 0; i < nodes; i++) {
		V[i] = i;
	}
}

// Wyswietlenie liczby miast oraz polaczen miedzy nimi
void Graph::printGraph() {
	std::cout << "\nLiczba miast: " << number_of_nodes << "\n\nLista polaczen miedzy miastami:\n\n";
	for (int i = 0; i < E.size(); i++) {
		std::cout << "Miasto startowe: " << E[i].second.first << " Miasto docelowe: " << E[i].second.second << "\n";
	}
}

void Graph::addEdge(int first_node, int second_node, int weight) {
	E.push_back(std::make_pair(weight, std::make_pair(first_node, second_node)));
}

// Tworzenie listy sasiedztw
void Graph::createdirE() {
	std::vector<int> row;
	for (int i = 0; i < E.size(); i++) {
		row.push_back(E[i].second.second);
		if (i == E.size() - 1) {
			directedE.push_back(row);
			row.clear();
			directedE.push_back(row);
			break;
		}
		if (E[i + 1].second.first != E[i].second.first) {
			directedE.push_back(row);
			row.clear();
		}
	}

	std::cout << "\n Lista grafu skierowanego\n\n";
	for (int i = 0; i < directedE.size(); i++) {
		std::cout << i + 1 << " -> ";
		for (int j = 0; j < directedE[i].size(); j++) {
			std::cout << directedE[i][j] + 1;
			if (j != directedE[i].size() - 1)
				std::cout << " -> ";
		}
		if (i + 1 == 18){
			std::cout << "NIL";
		}
		std::cout << "\n";
	}
}

// Tworzenie macierzy sasiedztw
void Graph::createundirE() {
	std::vector<int> row(number_of_nodes, 0);
	for (int i = 0; i < E.size(); i++) {
		row[E[i].second.second] = 1;
		if (i == E.size() - 1) {
			undirectedE.push_back(row);
			std::fill(row.begin(), row.end(), 0);
			undirectedE.push_back(row);
			break;
		}
		if (E[i + 1].second.first != E[i].second.first) {
			undirectedE.push_back(row);
			std::fill(row.begin(), row.end(), 0);
		}
	}
	// dodanie odwroconych polaczen (j,i)
	for (int i = 0; i < E.size(); i++) {
		undirectedE[E[i].second.second][E[i].second.first] = 1;
	}
	std::cout << "\n Macierz grafu nieskierowanego\n\n   ";
	for (int i = 0; i < number_of_nodes; i++) {
		if (i  >= 9) {
			std::cout << i + 1 << " ";
		}
		else {
			std::cout << i + 1 << "   ";
		}
	}
	std::cout << "\n";
	for (int i = 0; i < undirectedE.size(); i++) {
		std::cout << i + 1 << "  ";
		for (int j = 0; j < undirectedE[i].size(); j++) {
			if (j < 9) {
				std::cout << undirectedE[i][j] << "   ";
			}
			else {
				std::cout << undirectedE[i][j] << "  ";
			}
		}
		std::cout << "\n";
	}
}

// Przeszukiwanie w glab
void Graph::DFS() {
	std::vector <int> visited;
	std::vector <std::vector<int>> graph;
	int number_of_visited_cities = 0;
	int i = 0;
	bool end = false;
	std::vector <int> road;
	std::cout << "\nPrzeszukiwanie w glab\n";
	for (int j = 0; j < directedE.size(); j++) {
		graph.push_back(directedE[j]);
	}
	std::cout << "\n";
	for ( i = 0; i < directedE.size(); i++) {
		for (int j = 0; j < directedE[i].size(); j++) {
			if (graph[i][j] != i) {
				graph[graph[i][j]].push_back(i);
			}
		}
	}
	for (i = 0; i < graph.size(); i++) {
		std::sort(graph[i].begin(), graph[i].end());
	}
	i = 0;
	road.push_back(0);
	std::cout << "\n";
	while (end != true) {
		std::cout << "->" << i << "\n";
		bool next = false;
		if (std::find(visited.begin(), visited.end(), i) == visited.end() || visited.size() == 0) {
			visited.push_back(i);
			number_of_visited_cities++;
		}
		for (int j = 0; j < graph[i].size(); j++) {
			if (std::find(visited.begin(), visited.end(), graph[i][j]) == visited.end()) {
				if (graph[i][j] != visited.back()) {
					road.push_back(graph[i][j]);
					i = graph[i][j];
					next = true;
					break;
				}
			}
		}
		if (next == false && road.size() >= 2) {
			road.pop_back();
			i = road.back();
		}
		if (i == 0 && number_of_visited_cities) {
			while (end != true) {
				std::cout << "->" << i << "\n";
				if (i != 0) {
					road.pop_back();
					i = road.back();
				}
				else {
					end = true;
				}
			}
		}
	}
	std::cout << "\n\n";
}

// Przeszukiwanie wszerz
void Graph::BFS() {
	std::vector <int> visited;
	std::vector <std::vector<int>> graph;
	int number_of_visited_cities = 1;
	int i = 0;
	bool end = false;
	std::vector <int> road;
	std::cout << "\nPrzeszukiwanie wszerz\n";
	for (int j = 0; j < directedE.size(); j++) {
		graph.push_back(directedE[j]);
	}
	std::cout << "\n";
	for (i = 0; i < directedE.size(); i++) {
		for (int j = 0; j < directedE[i].size(); j++) {
			if (graph[i][j] != i) {
				graph[graph[i][j]].push_back(i);
			}
		}
	}
	for (i = 0; i < graph.size(); i++) {
		std::sort(graph[i].begin(), graph[i].end());
	}
	i = 0;
	road.push_back(0);
	visited.push_back(0);
	std::cout << " " << i << "\n";
	while (end != true) {
		for (int j = 0; j < graph[i].size(); j++) {
			if (std::find(visited.begin(), visited.end(), graph[i][j]) == visited.end()) {
				if (graph[i][j] != visited.back()) {
					visited.push_back(graph[i][j]);
					road.push_back(graph[i][j]);
					number_of_visited_cities++;
				}
			}
		}
		road.erase(road.begin());
		i = road[0];
		std::cout << " ";
		for (int j = 0; j < road.size(); j++) {
			std::cout << road[j] << " ";
		}
		if (number_of_visited_cities == 18 && road.size() == 1) {
			end = true;
			break;
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

int main() {
	Graph g(18);
	std::ifstream file("Weights.txt");
	std::ifstream sfile("Cities.txt");
	std::string line;
	int line1 = -1, line2 = -1, line3 = -1;
	int tmp;
	while (file >> tmp) {
		if (line1 == -1) {
			line1 = tmp;
		}
		else {
			if (line2 == -1) {
				line2 = tmp;
			}
			else {
				if (line3 == -1) {
					line3 = tmp;
				}
			}
		}
		if (line1 != -1 && line2 != -1 && line3 != -1) {
			g.addEdge(line1, line2, line3);
			line1 = -1;
			line2 = -1;
			line3 = -1;
		}
	}
	file.close();
	std::cout << "Lista miast" << "\n\n";
	while (std::getline(sfile, line)) {
		std::cout << line << "\n";
	}
	sfile.close();
	g.printGraph();
	g.createundirE();
    g.createdirE();
	g.DFS();
	g.BFS();
	return 0;
}