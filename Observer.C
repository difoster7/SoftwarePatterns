#include "Observer.H"
#include "ChangeManager.H"

NewNodeObserver_Impl::NewNodeObserver_Impl()
{
	ChangeManager* chngMngr = new ChangeManager_Impl();
	chngMngr->registerObserver(ChangeManager::ChangeType::NEW_NODE, this);
}

NewNodeObserver_Impl::~NewNodeObserver_Impl()
{
	ChangeManager* chngMngr = new ChangeManager_Impl();
	chngMngr->deregisterObserver(ChangeManager::ChangeType::NEW_NODE, this);
}

void NewNodeObserver_Impl::update(dom::Node* node)
{
	printf("New node created! Node name: %s\n", node->getNodeName().c_str());
}

NodeCompleteObserver_Impl::NodeCompleteObserver_Impl()
{
	ChangeManager* chngMngr = new ChangeManager_Impl();
	chngMngr->registerObserver(ChangeManager::ChangeType::NODE_COMPLETE, this);
}

NodeCompleteObserver_Impl::~NodeCompleteObserver_Impl()
{
	ChangeManager* chngMngr = new ChangeManager_Impl();
	chngMngr->deregisterObserver(ChangeManager::ChangeType::NODE_COMPLETE, this);
}

void NodeCompleteObserver_Impl::update(dom::Node* node)
{
	printf("Node complete: %s\n", node->getNodeName().c_str());
}
