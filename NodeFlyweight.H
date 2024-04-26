#ifndef NODE_FLYWEIGHT_H
#define NODE_FLYWEIGHT_H

#include "Node.H"

namespace dom
{
	// Flyweight Pattern : Abstract Flyweight
	class NodeFlyweight : public virtual Node
	{
	private:
		virtual Node* findChild(Node* parent, std::string name) = 0;

	public:
		virtual Node* getParentNode(std::string name) = 0;	// Flyweight pattern : opreation(extrinsic state)
	};
}

// Flyweight Pattern : Concrete Flyweight
class NodeFlyweight_Impl : public virtual dom::NodeFlyweight, public virtual Node_Impl
{
private:
	virtual Node* findChild(Node* parent, std::string name);

public:
	virtual Node* getParentNode(void);
	virtual Node* getParentNode(std::string name);	// Flyweight pattern : opreation(extrinsic state)

	virtual void setParent(dom::Node* parent);

};


#endif // !NODE_FLYWEIGHT_H
