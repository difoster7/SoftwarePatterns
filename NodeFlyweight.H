#ifndef NODE_FLYWEIGHT_H
#define NODE_FLYWEIGHT_H

#include "Node.H"

namespace dom
{
	class NodeFlyweight : public virtual Node
	{
	private:
		Node* findChild(Node* parent, std::string name);

	public:
		virtual Node* getParentNode(void);
		virtual Node* getParentNode(std::string name);
	};
}


#endif // !NODE_FLYWEIGHT_H
