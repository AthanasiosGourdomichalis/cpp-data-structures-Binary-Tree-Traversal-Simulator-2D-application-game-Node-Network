#pragma once
#include<string>
class Interactable { // Interface Class for GUI elements that the user can interact with when his mouse hovers/clicks/drags etc. (Nodes, Buttons, the Grid etc.)
	virtual bool contains() = 0; 
	
};
//e.g.
//Point Containment Check in a Rectangle (class Button) in "Button.cpp"
//Point Containment Check in a Circle (class Node) in "Node.h"
//Point Containment Check in a Rectangle (class Grid) in "Grid.cpp" etc.
