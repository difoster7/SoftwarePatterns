#ifndef NODE_FLYWEIGHT_H
#define NODE_FLYWEIGHT_H

#include "Node.H"

namespace dom
{
	class NodeFlyweight : public virtual Node
	{
	private:
		virtual Node* findChild(Node* parent, std::string name) = 0;

	public:
		virtual Node* getParentNode(void) = 0;
		virtual Node* getParentNode(std::string name) = 0;
	};
}

class NodeFlyweight_Impl : public virtual dom::NodeFlyweight, public virtual Node_Impl
{
private:
	virtual Node* findChild(Node* parent, std::string name);

public:
	virtual Node* getParentNode(void);
	virtual Node* getParentNode(std::string name);

	virtual void setParent(dom::Node* parent);

};


#endif // !NODE_FLYWEIGHT_H
