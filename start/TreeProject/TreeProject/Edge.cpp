#include "Edge.h"

void Edge::init() {
	edge_br.outline_opacity = 0.0f;
	SETCOLOR(edge_br.outline_color, 0.0f, 0.0f, 0.0f);
}
void Edge::draw() {
	graphics::drawLine(startNode->getX(),startNode->getY(), endNode->getX(), endNode->getY(), edge_br);

}
void Edge::update() {

}