#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "Node.H"

namespace dom
{
	class CompositeNode : public virtual Node
	{
	public:
		virtual ~CompositeNode() {}

		virtual NodeList* getChildNodes(void) = 0;
		virtual Node* getFirstChild(void) = 0;
		virtual Node* getLastChild(void) = 0;
		virtual Node* insertBefore(Node* newChild, Node* refChild) = 0;
		virtual Node* replaceChild(Node* newChild, Node* oldChild) = 0;
		virtual Node* removeChild(Node* oldChild) = 0;
		virtual Node* appendChild(Node* newChild) = 0;
		virtual bool hasChildNodes(void) = 0;
	};
}

class CompositeNode_Impl : public virtual dom::CompositeNode, Node_Impl
{
protected:
	CompositeNode_Impl(const std::string& name, short type) : Node_Impl(name, type) {}

public:
	virtual ~CompositeNode_Impl() {}

	virtual dom::NodeList* getChildNodes(void);
	virtual Node* getFirstChild(void);
	virtual Node* getLastChild(void);
	virtual Node* insertBefore(Node* newChild, Node* refChild);
	virtual Node* replaceChild(Node* newChild, Node* oldChild);
	virtual Node* removeChild(Node* oldChild);
	virtual Node* appendChild(Node* newChild);
	virtual bool hasChildNodes(void);

};


#endif // !COMPOSITENODE_H
