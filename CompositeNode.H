#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "Node.H"

namespace dom
{
	// Composite Pattern Composite Component Interface
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

		virtual Node* getChild(int n) = 0;
	};
}

// Composite Pattern Composite Component Implementation
// Defines child management functions for composites
class CompositeNode_Impl : public virtual dom::CompositeNode, virtual public Node_Impl
{
protected:
	CompositeNode_Impl(const std::string& name, short type, dom::Document* doc);

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

	virtual Node* getChild(int n);

};


#endif // !COMPOSITENODE_H
