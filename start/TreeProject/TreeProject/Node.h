#pragma once
#include"Widget.h"
#include <cmath>
#include "sgg/graphics.h"
#include "setColor.h"
using namespace std;

template <typename T>
// implements the Interactable interface, to have the "contains()" method (Point Containment Check in a Circle)
class Node: public Widget, public Interactable {//extends Widget class because it is a GUI element
	const T id;					//the node's data (type Template)
	const float radius = 40.0f;
	bool active;				//used in visualization level to change the nodes' color during the traversal
	bool hover;					//used in the Grid class for the node's child-boxes visualization
	Node* parent=nullptr;		//the node's parent and child references
	Node* leftChild = nullptr;
	Node* rightChild = nullptr; //the node's brushes
	graphics::Brush node_br;
	graphics::Brush text_br;
	graphics::Brush box_br;
public:
	Node(float x, float y,T id, float r = 0.6f,float g = 0.8f, float b = 1.0f, const std::string& img = "") ://constructor
	Widget(x, y, r, g, b, img), id(id){
		hover = false;
		active = false;
	}
	~Node() {}		//destructor
	void init() {
		node_br.gradient = true;
		node_br.fill_opacity = 1.0f;
		node_br.outline_opacity = 1.0f;
		node_br.outline_width = 2.0f;
		SETCOLOR(node_br.outline_color, 0.1f, 0.2f, 0.4f);
		SETCOLOR(node_br.fill_color, r, g, b);
		SETCOLOR(node_br.fill_secondary_color, 0.2f, 0.4f, 0.7f);

		node_br.gradient_dir_u = 0.0f;
		node_br.gradient_dir_v = 1.0f;

		text_br.fill_opacity = 1.0f;
		text_br.outline_opacity = 0.0f;

		SETCOLOR(text_br.fill_color, 0.2f, 0.2f, 0.2f);

		box_br.fill_opacity = 0.8f;
		box_br.outline_opacity = 0.0f;
		SETCOLOR(box_br.fill_color, 0.3f, 0.75f, 0.45f);
		

	
	};
	void draw() {
		std::string text(1, id);
		graphics::drawDisk(pos_x, pos_y, radius, node_br);
		graphics::drawText(pos_x-7, pos_y+10, 30.0f, text, text_br);
		if (hover==true) { //the node's children boxes, used in the grid class to check its available children 
			if (leftChild == nullptr) {
				graphics::drawRect(pos_x - 30, pos_y + 30, 20.0f, 20.0f, box_br);
			}
			if (rightChild == nullptr) {
				graphics::drawRect(pos_x + 30, pos_y + 30, 20.0f, 20.0f, box_br);
			}

		}
		
	};
	void update() {
		graphics::MouseState ms;
		graphics::getMouseState(ms);

		if (active) {//change the nodes' color from blue to yellow
			SETCOLOR(node_br.outline_color, 1.0f, 0.9f, 0.2f);
			SETCOLOR(node_br.fill_color, 0.8f, 0.6f, 0.1f);
			SETCOLOR(node_br.fill_secondary_color, 1.0f, 0.7f, 0.0f);
		}
		else if (contains()) { //change the nodes' color to darker blue when we hover over them with our mouse
			SETCOLOR(node_br.fill_color, r * 0.7f, g * 0.7f, b * 0.7f);
		}
		else {		//else, set the color to default
			SETCOLOR(node_br.outline_color, 0.1f, 0.2f, 0.4f);
			SETCOLOR(node_br.fill_color, r, g, b);
			SETCOLOR(node_br.fill_secondary_color, 0.2f, 0.4f, 0.7f);
		}
	};
	const float getRadius() const{ //getter
		return radius;

	}
	bool contains(){ //Point Containment Check in a Circle
		graphics::MouseState ms;
		graphics::getMouseState(ms);
		float mx = graphics::windowToCanvasX(ms.cur_pos_x);
		float my = graphics::windowToCanvasY(ms.cur_pos_y);
		return std::sqrt(std::pow(mx - pos_x, 2) + std::pow(my - pos_y, 2)) < radius;
	
	};

	//getters
	Node<char>* getRightChild() {
		return rightChild;
	}

	Node<char>* getLeftChild() {
		return leftChild;
	}

	//setters
	void setLeftChild(Node<char>* child) {
		leftChild = child;
	}

	void setRightChild(Node<char>* child) {
		rightChild = child;
	}
	void setParent(Node<char>* Newparent) {
		parent = Newparent;
	}


	void setPosition(float new_x, float new_y){
		setX(new_x); setY(new_y);				//used in the Grid class to change the nodes' coordinates when dragging a node
	}

	void setHover(bool flag) {
		hover=flag;
	}
	void setActive(bool flag) {
		active = flag;
	}
	bool hasParent() {
		return parent != nullptr;
	}

	string getLetter() {
		std::string letter(1, id);
		return letter;
	}
	
};