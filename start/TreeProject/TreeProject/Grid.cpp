#include "Grid.h"
#include "setColor.h"

void Grid::updateOrder() {
    order = nodes.size();
}
void Grid::init() {
    updateOrder();//get the correct letter order for the nodes when coming back from the visualization level
    //initialize grid colors
	grid_br.outline_opacity = 0.0f;
	grid_br.texture = "assets/grid.png";
	SETCOLOR(grid_br.fill_color, r, g, b);
    line.outline_width = 3.0f; 
    line.fill_opacity = 0.0f;
    SETCOLOR(line.outline_color, 0.0f, 0.0f, 0.0f);
	
	
	
}
void Grid::draw() {
    
    graphics::MouseState ms;
    graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	graphics::drawRect(pos_x, pos_y, width, height, grid_br);//draws the grid
	for (Node<char>* n : nodes) {
		n->draw(); //draw each node
	}
    for (Edge* e : edges) {
        e->draw(); //draw each edge
    }
    /*when a child node is selected as a starting node (child!=nullptr)
    begin to draw a line from the child following the mouse as end coordinates */
    if (child!=nullptr) {
        float x = child->getX();
        float y = child->getY();
        float dist = std::abs(my - y);
        float ep1[2] = { x,y };
        float cp1[2] = { x, y - dist * 0.3f };
        float cp2[2] = { mx, my + dist * 0.3f };
        float ep2[2] = { mx,my};

        graphics::drawBezier(ep1, cp1, cp2, ep2, line);
    }
}
void Grid::update() {

    for (Node<char>* n : nodes) {
        n->update();//update each node
    }

    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    if (contains()) {//when above a node
        if (ms.button_left_pressed) {//if we press the left button
            if (movingNode == nullptr) {//if we arent already dragging a node
                //find the node we are trying to move
                for (Node<char>* n : nodes) {
                    if (n->contains()) {
                        movingNode = n;

                        break;//when found brake
                    }
                }
            }
            if (intercepts(mx, my) == false) {//if we are not trying to place a node above another node
                Node<char>* n = new Node<char>(mx, my, 'A' + order);//create a new node ('A' + order = letter according to its order)
                order++;
                addNode(n); //add to the Node-Vector
                
            }
        }
        if (ms.button_left_down && movingNode != nullptr) {//if we are dragging the mouse with the left button and we have found a node
            movingNode->setPosition(mx, my);//update constantly it's position
        }
        if (ms.button_left_released && movingNode != nullptr) {//when left button released and we are dragging a node
            movingNode->setPosition(mx, my);//set it's final position
            if (intercepts(mx, my, movingNode)) {//if it's above another node
                movingNode->setPosition(mx + 50, my + 50);//push it further down right
            }

            movingNode = nullptr;//stop moving the node
        }
        if (ms.button_right_pressed && !child) {//if we press the right button and we havent found a node

            for (Node<char>* n : nodes) {
                if (n->contains() && !n->hasParent()) {//if it doesn't already have a parent
                    child = n;//find the child we are trying to connect
                    
                    break;//when found, break
                }
            }
        }
        if (ms.button_right_down && child) {//when the right button is released and we are dragging an edge from the child
            parent = nullptr;//havent found the parent node yet
            for (Node<char>* n : nodes) {
                if (n->contains() && n != child) {//if above a potential parent node
                    parent = n;
                    parent->setHover(true);//show available children's boxes
                    break;
                }

            }
            if (!parent) {//if not above potential parent remove hover boxes
                for (Node<char>* n : nodes) n->setHover(false);
            }


        }
        else if (ms.button_right_released && child) {//if the right button is released and we are dragging an edge from the child

            
            if (parent) {//if above a potential parent node
                bool connection = false;
                float px = parent->getX(); //get the parent's coordinates
                float py = parent->getY();
                //check, if trying to connect to the left box, if available
                if (mx >= px - 45 && mx <= px - 15 && my >= py + 15 && my <= py + 45 && parent->getLeftChild() == nullptr) {
                    parent->setLeftChild(child); //update the parent's pointer to the left child
                    connection = true; 
                }

				//check, if trying to connect to the right box, if available
                else if (mx >= px + 15 && mx <= px + 45 && my >= py + 15 && my <= py + 45 && parent->getRightChild() == nullptr) {
                    
                    parent->setRightChild(child); //update the parent's pointer to the right child
                    connection = true;
                }
                if (connection) {
                    addEdge(new Edge(child, parent));//create connecting edge between parent and child
                    child->setParent(parent);//update child's parent
                }
                parent->setHover(false); 
            }

            child = nullptr;
            parent = nullptr;
        }

    }
}
bool Grid::contains() { //Point Containment Check in a Rectangle
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	return (pos_x - width / 2+40 <= mx && mx <= pos_x + width / 2-40) && (pos_y - height / 2+40 <= my && my <= pos_y + height / 2-40);
}
//Disk Overlap Check 
bool Grid::intercepts(float x, float y, Node<char>* ignore) {
	for (Node<char>* n : nodes) {
        if (n == ignore) continue;//does not check the node we are currently moving
		float dx = x - n->getX();
		float dy = y - n->getY();
		float distance = std::sqrt(dx * dx + dy * dy);


		if (distance < n->getRadius() + 25.0f) {
			return true;

		}
	}
	return false;
}

void Grid::addNode(Node<char>* n) {
	nodes.push_back(n);
	n->init();
}

void Grid::addEdge(Edge* e) {
    edges.push_back(e);
    e->init();
}







