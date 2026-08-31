#pragma once
#include "Widget.h"
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <string>
class Grid : public Widget, public Interactable {
protected:
	const float width;
	const float height;
	std::vector<Node<char>*> nodes; 
	std::vector<Edge*> edges;
	int order;//to retrieve (get) which letter each node should have
	graphics::Brush grid_br;
	graphics::Brush line;
	Node<char>* head;//tree head
	Node<char>* movingNode;//when trying to move a node
	Node<char>* child;//the child from which we are trying to connect an edge
	Node<char>* parent;//the parent to whom we are trying to connect an edge




public:

	Grid(const std::vector<Node<char>*>& nodes, const std::vector<Edge*>& edges, 
		float x, float y, float w, float h, float r = 1.0f, float g = 1.0f, float b = 1.0f, const std::string& img = "") :
		nodes(nodes), edges(edges), Widget(x, y, r, g, b, img), width(w), height(h) {

		head = nullptr;
		movingNode = nullptr;//we are not moving a node
		order = 0;//to begin with the first letter = 'A'
		//we are not connecting an edge
		child = nullptr;
		parent = nullptr;
	}


	~Grid() {
		//nodes & edges are deleted in EditingLevel destructor
	}


	void init();
	void draw();
	void update();
	bool contains()override;

	//Disk Overlap Check 
	bool intercepts(float x, float y, Node<char>* ignore = nullptr);//to check if a moving node is placed above another node

	void addNode(Node<char>* n);
	void addEdge(Edge* e);
	void updateOrder();//get the correct step for the nodes when going back from visualizationLevel

	std::vector<Node<char>*> getNodes() {//returns the nodes to the visualizationLevel
		return nodes;
	}
	std::vector<Edge*> getEdges() {//returns the edges to the visualizationLevel
		return edges;
	}
	void clearVectors() {
		nodes.clear();
		edges.clear();
	}
	
	


};
