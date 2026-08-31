#pragma once


class GameObject {//Generic (interface) base class for the application's window elements with x,y coordinates at the center
protected:
    float pos_x;//the center of each gameobject
    float pos_y;
	GameObject(float x, float y) : pos_x(x), pos_y(y) {};//an abstract's class constructor can't be called directly
    
public:
    virtual ~GameObject() {} //abstract constructor for polymorphism 


    virtual void update() = 0; //pure virtual (abstract) methods
    virtual void draw() = 0;
    virtual void init() = 0;

    //setters and getters for x and y
    float getX() const { return pos_x; }//const to make sure it does not alter the node's properties
    float getY() const { return pos_y; }
    void setX(float new_x) { pos_x = new_x; }
	void setY(float new_y) { pos_y = new_y; }
    
    
};