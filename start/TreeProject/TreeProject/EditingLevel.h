#pragma once
#include "Levels.h"
#include "Grid.h"
class EditingLevel:public Levels {
	Grid* grid;
	std::vector<Node<char>*> nodes;//to get the nodes from the visualizationLevel when "back" is pressed 
	std::vector<Edge*> edges;//to get the edges from the visualizationLevel when "back" is pressed 
public:
	//when created for the first time nodes and edges are empty
	EditingLevel(const std::vector<Node<char>*>& nodes = std::vector<Node<char>*>(), const std::vector<Edge*>& edges = std::vector<Edge*>()) : 
	nodes(nodes), edges(edges) {
		grid = nullptr;
	}


	~EditingLevel() {//deletes nodes and edges
		for (auto n : nodes) {
			delete n;
		}
		for (auto e : edges) {
			delete e;
		}
	};
		
	void clearVectors() {//clears nodes' and edges' pointers 
		nodes.clear();
		edges.clear();
	}

	void init();
	void draw();
	void update();
};



