#ifndef EventHandler_H
#define EventHandler_H

#include <list>

#include "Node.H"

class EventHandler {
private:
	inline static dom::NodeList handlers;

public:
	EventHandler() {};
	void addhandler(dom::Node* newHandler) { handlers.push_back(newHandler); }
	dom::NodeList* getHandlers() { return &handlers; }
};


#endif // !EventHandler_H
