#pragma once
#include "Node.h"


class Edge {
	//the first const is because it does not alter the node's properties, the second const is because it cant point to another node after initialization
	const Node<char>* const startNode;//to get the starting coordinates of the edge 
	const Node<char>* const endNode;//to get the ending coordinates of the edge
	graphics::Brush edge_br;


public:
	Edge(Node<char>* first, Node<char>* second):startNode(first), endNode(second){}

	void init() {
		edge_br.outline_opacity = 1.0f;
		edge_br.outline_width = 6.0f;
		SETCOLOR(edge_br.outline_color, 0.1f, 0.2f, 0.4f);
	};
	void draw() {
		float x1 = startNode->getX();
		float y1 = startNode->getY();
		float x2 = endNode->getX();
		float y2 = endNode->getY();
		float dist = std::abs(y2 - y1);
		float ep1[2] = { x1,y1 - 40 };// -40 to start from the edge of the node
		float cp1[2] = { x1, y1 - dist * 0.3f };//controls the first curb of the line
		float cp2[2] = { x2, y2 + dist * 0.3f };//controls the second curb of the line
		float ep2[2] = { x2,y2 + 40 }; // +40 to end on the edge of the node

		graphics::drawBezier(ep1, cp1, cp2, ep2, edge_br);

	};
	
};




