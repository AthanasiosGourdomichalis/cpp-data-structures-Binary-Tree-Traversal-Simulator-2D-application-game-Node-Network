#pragma once
#include "Levels.h"
#include "string"
#include "Box.h"

class VisualizationLevel :public Levels {
	graphics::Brush box_br;
	//the nodes and edges passed by the Grid
	std::vector<Node<char>*> nodes; 
	std::vector<Edge*> edges;
					
	std::vector<Node<char>*> tempNodes;//helper Vector consisting of the nodes in order of the traversal chosen
	std::vector<Box*> boxes;		//nodes visualization boxes
	Label* traversalLabel = nullptr;   //chosen traversal Label
	float startX = 0.0f;//where the boxes should start to be drawn
	int step;		//helper counter for tempNodes traversal
	bool visualization; //check if we have started the visualization process
	//Used to add delay between each step of the visualization
	float now; 
	float lastTime;	
	std::string traversal;	//the selected traversal
public:
	VisualizationLevel(vector<Node<char>*> nodes, vector<Edge*> edges) :nodes(nodes), edges(edges), step(0), visualization(false), now(0.0f), lastTime(0.0f) {

	};
	~VisualizationLevel() { //delete this level's dynamic memory
		for (Node<char>* n : nodes) {
			delete n;
		}
		for (Edge* e : edges) {
			delete e;
		}

	}
	void init();
	void draw();
	void update();
	void removeLoneNodes() { //removes any nodes made by the user that dont belong in the tree
		auto iter = nodes.begin();

		while (iter != nodes.end()) {
			Node<char>* currentNode = *iter;
			if (!currentNode->hasParent() && (!currentNode->getLeftChild() && !currentNode->getRightChild())) { //a node does not belong in the tree if it does not have neither a parent, nor child-nodes
				delete currentNode;  //deletes any nodes made in the editing level that dont belong in the tree 
				iter = nodes.erase(iter); //removes the current node and sets the remaining nodes one position to the left
			}
			else {
				++iter;
			}
		}
	}
	void addBox(Box* b) {	//adds a node-box during the visualization
		boxes.push_back(b);
		b->init();
	}
	//our 4 tree traversal methods
	void inorder(Node<char>* head);
	void preorder(Node<char>* head);
	void postorder(Node<char>* head);
	void levelorder(Node<char>* head);
	
	void setUp();

	Node<char>* findHead();

	std::vector<Node<char>*> getNodes() {//getters for nodes and edges to return them back to the editing level
		return nodes;
	}
	std::vector<Edge*> getEdges() {
		return edges;
	}
	void clearVectors() {//clears nodes and edges pointers 
		nodes.clear();
		edges.clear();
	}
};
