#include "EditingLevel.h"
#include "StartLevel.h"
#include "VisualizationLevel.h"
#include "Grid.h"
#include "GlobalState.h"
#include <queue>
#include <stack>


void VisualizationLevel::init() {
    removeLoneNodes();
    startX = (GlobalState::getInstance()->CANVAS_WIDTH / 2.0f) - (nodes.size() * 80.0f / 2.0f) + (80.0f / 2.0f); //updates the starting point of the boxes according to the new number of nodes
    traversal = GlobalState::getInstance()->getTraversal();//gets the traversal that the user selected in the home screen
    box_br.fill_opacity = 1.2f;
    box_br.outline_opacity = 0.0f;
    box_br.texture = "assets/grid.png";
    SETCOLOR(box_br.outline_color, 0.0f, 0.0f, 0.0f);
    SETCOLOR(box_br.fill_color, 1.0f, 1.0f, 1.0f);
    
    //set the background color
    addGameObject(new Background(0.125f, 0.165f, 0.196f));
    //Chosen traversal's label
    traversalLabel = new Label(getOffset(GlobalState::getInstance()->CANVAS_WIDTH / 2, 50, traversal), 50, 0.867f, 0.902f, 0.929f, 50, traversal);
    addGameObject(traversalLabel);
    //"Back" button and its label 
    addGameObject(new Label(getOffset(220, 30, "Continue Editing"), 850, 0.616f, 0.698f, 0.749f, 30, "Continue Editing"));
    addGameObject(new Button(200, 900, 100, 50, 0.322f, 0.427f, 0.510f, " ", "Back"));
    addGameObject(new Label(getOffset(200, 20, "Back"), 905, 0.867f, 0.902f, 0.929f, 20, "Back"));
    //"Home" button and its label 
    addGameObject(new Label(getOffset(210, 30, "Go to Home Page"), 150, 0.616f, 0.698f, 0.749f, 30, "Go to Home Page"));
    addGameObject(new Button(200, 200, 100, 50, 0.322f, 0.427f, 0.510f, " ", "Home"));
    addGameObject(new Label(getOffset(195, 20, "Home"), 200, 0.867f, 0.902f, 0.929f, 20, "Home"));
    //buttons for each traversal and their label 
    addGameObject(new Label(getOffset(1340, 35, "Change-Traversal"), 120, 0.867f, 0.902f, 0.929f, 35, "Change-Traversal"));
    addGameObject(new Button(1340, 200, 100, 50, 0.322f, 0.427f, 0.510f, " ", "preorder"));
    addGameObject(new Label(getOffset(1340, 20, "preorder"), 200, 0.867f, 0.902f, 0.929f, 20, "preorder"));
    addGameObject(new Button(1340, 300, 100, 50, 0.322f, 0.427f, 0.510f, " ", "inorder"));
    addGameObject(new Label(getOffset(1340, 20, "inorder"), 300, 0.867f, 0.902f, 0.929f, 20, "inorder"));
    addGameObject(new Button(1340, 400, 100, 50, 0.322f, 0.427f, 0.510f, " ", "postorder"));
    addGameObject(new Label(getOffset(1340, 20, "postorder"), 400, 0.867f, 0.902f, 0.929f, 20, "postorder"));
    addGameObject(new Button(1340, 500, 100, 50, 0.322f, 0.427f, 0.510f, " ", "levelorder"));
    addGameObject(new Label(getOffset(1345, 20, "level-order"),500, 0.867f, 0.902f, 0.929f, 20, "level-order"));
    //"Start" button and its label 
    addGameObject(new Button(1340, 900, 100, 50, 0.322f, 0.427f, 0.510f, " ", "Start"));
    addGameObject(new Label(getOffset(1340, 20, "Start"), 905, 0.867f, 0.902f, 0.929f, 20, "Start"));
    addGameObject(new Label(getOffset(1355, 30, " Press 'start' to"), 750, 0.616f, 0.698f, 0.749f, 30, " Press 'start' to"));
    addGameObject(new Label(getOffset(1355, 30, "start Tree"), 790, 0.616f, 0.698f, 0.749f, 30, "start Tree"));
    addGameObject(new Label(getOffset(1355, 30, "traversal Visualization"), 830, 0.616f, 0.698f, 0.749f, 30, "traversal Visualization"));
    //header for the boxes array
    addGameObject(new Label(getOffset(750, 30, "Nodes Order"), 900, 0.867f, 0.902f, 0.929f, 30, "Nodes Order"));

}
void VisualizationLevel::draw() {
    Levels::draw();
    graphics::drawRect(GlobalState::getInstance()->CANVAS_WIDTH / 2, GlobalState::getInstance()->CANVAS_HEIGHT / 2-50, 750, 750, box_br);
    for (Node<char>* n : nodes) {
        n->draw();
    }
   
    for (Edge* e : edges) {
        e->draw();
    }

    for (Box* b : boxes) {
        b->draw();
    }
}
//helper method to find the head of the tree
Node<char>* VisualizationLevel::findHead() {
    for (Node<char>* n : nodes) {
        if (!n->hasParent() && (n->getLeftChild() || n->getRightChild())) return n;//must have at least one child and no parent
    }
    return nullptr;
}
void VisualizationLevel::inorder (Node<char>* head){ //recursive method that gives us the sequence of the nodes according to inorder traversal
	if (head==nullptr){return;} //base of recursion
    
    inorder(head->getLeftChild());  //first call the method for the head's left subtree
    tempNodes.push_back(head);      //push the current node in the temporary visualization vector 
    addBox(new Box(startX + boxes.size() * 80, 950, head->getLetter()));    //add the current nodes visualization box in its vector respectively
    inorder(head->getRightChild());    //call the method for the node's right subtree

}
//current node->left subtree-> right subtree
void VisualizationLevel::preorder(Node<char>* head) { //helper method to get the node's sequence accordind to the preorder traversal
	stack<Node<char>*> NodeStack ;//we use an STL stack to get the correct sequence
    NodeStack.push(head);   //first we push the head of the tree in the temporary vector
    while(!NodeStack.empty()){
        Node<char> * current = NodeStack.top(); 
        NodeStack.pop();    
        tempNodes.push_back(current);   //push the current node
        addBox(new Box(startX + boxes.size() * 80, 950, current->getLetter())); //add the respective visualization box
        if (current->getRightChild()) { NodeStack.push(current->getRightChild()); } //first we push the right subtree
		if (current->getLeftChild()) { NodeStack.push(current->getLeftChild()); } //then the left subtree 
        //the subtrees are pushed in the opposite sequence , because of the LIFO (last in first out) rule, we will visualize the left subtree before the right one


    }

        
        

	
}

void VisualizationLevel::postorder(Node<char>* head) {  //recursive method for the postorder traversal, similar to the inorder method 
	if (head == nullptr) { return; }
    postorder(head->getLeftChild());    //we only change the recursion's sequence to left subtree->right subtree->head
	postorder(head->getRightChild());   
    tempNodes.push_back(head);
    addBox(new Box(startX + boxes.size() * 80, 950, head->getLetter()));//add the nodes visualization box to the respective vector

}

void VisualizationLevel::levelorder(Node<char>* head) { //in this traversal we use a queue to get the correct sequence of the nodes 
    queue<Node<char>*> NodeQueue;
    NodeQueue.push(head); //first we push the head of the tree

    while(!NodeQueue.empty()){
        Node<char>* current = NodeQueue.front(); //dequeue the current node
        NodeQueue.pop();
        if (current == nullptr) continue; 
		tempNodes.push_back(current); //push the current node in the temporary vector
        addBox(new Box(startX + boxes.size() * 80, 950, current->getLetter())); //add its visualization box
        if (current->getLeftChild()!=nullptr) { NodeQueue.push(current->getLeftChild()); } //first we enqueue the left child
		if (current->getRightChild() != nullptr) { NodeQueue.push(current->getRightChild()); } //then the right child
        //because of the queue's FIFO (first in first out) rule, the temporary vector nodes sequence will be head->left child->right child, from top to bottom and from left to right
    }
    

}
void VisualizationLevel::setUp() {
    //make sure all vectors are empty
    tempNodes.clear();
    boxes.clear();
    //run the correct traversal to initialize temporary (temp)nodes and boxes
    if (traversal == "inorder") {
        inorder(findHead());
    }
    if (traversal == "postorder") {
        postorder(findHead());
    }
    if (traversal == "preorder") {
        preorder(findHead());
    }
    if (traversal == "levelorder") {
        levelorder(findHead());
    }
    //get the current time
    lastTime = graphics::getGlobalTime();
    //start visualization
    visualization = true;
    step = 0;
    
}

void VisualizationLevel::update() {
    Levels::update();
    for (Box* b : boxes) {
        b->update();
    }
	for (Node<char>* n : tempNodes) {
		n->update();
	}
	const std::string& btn = GlobalState::getInstance()->getButtonID();//get the last button pressed
    now = graphics::getGlobalTime();
    if (btn == "Back") {
        GlobalState::getInstance()->setButtonID("");
        for (Node<char>* n : nodes) {
            n->setActive(false);//if the "back" button is pressed while in visualization process, it resets the nodes' color
        }
        EditingLevel* newLevel = new EditingLevel(getNodes(), getEdges());
        clearVectors();
        GlobalState::getInstance()->changeLevel(newLevel);//change Level to editing level

    }
    if (btn == "Home") {
        GlobalState::getInstance()->setButtonID("");
        GlobalState::getInstance()->changeLevel(new StartLevel());//change Level to StartLevel

    }
    if (btn == "preorder" || btn == "inorder" ||
        btn == "postorder" || btn == "levelorder") {
        GlobalState::getInstance()->setTraversal(btn);//sets the new traversal
        traversal = GlobalState::getInstance()->getTraversal();//updates the traversal in the current level
        traversalLabel->setText(btn);//update the Traversal Label text
        traversalLabel->setX(getOffset(GlobalState::getInstance()->CANVAS_WIDTH / 2, 50, btn));//update the Traversal Label x point
        GlobalState::getInstance()->setButtonID("");
    }
    if (btn  == "Start") {
        GlobalState::getInstance()->setButtonID("");
        if (!nodes.empty()) {
            setUp();//initialize visualization process
        }

    }
    
    if (visualization) {//if we are in the visualization process
        if(now-lastTime>1000){//if we have exceeded the delay 
            if (step >= tempNodes.size()) {//chech if we have passed all the nodes
                visualization = false;//end visualization
                //deactivate last node
                tempNodes[step - 1]->setActive(false);
                boxes[step - 1]->setActive(false);
                //plays end sound
                graphics::playSound("assets/done.wav", 1.0f, false);
            }else{
                if (step > 0) {
                    //deactivate last node and activate current node
                    tempNodes[step - 1]->setActive(false);
                    boxes[step-1]->setActive(false);
                    tempNodes[step]->setActive(true);
                    boxes[step]->setActive(true);
                    //play sound when the node is changed
                    graphics::playSound("assets/select.wav", 1.0f, false);

                }
                //activate first node
                tempNodes[step]->setActive(true);
                boxes[step]->setActive(true);
                graphics::playSound("assets/select.wav", 1.0f, false);
                step++;
                lastTime = now;//update last time
            }
           
        }
        


    }
}