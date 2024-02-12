#include "NodeIter.H"

NodeIter_Impl::NodeIter_Impl(dom::CompositeNode* first) : first(first), done(false)
{
}

dom::Node* NodeIter_Impl::start()
{
	done = false;
	memento.initialize(first);
	return first;
}

dom::Node* NodeIter_Impl::next()
{
	dom::Node* comp;
	int index;
	memento.getAndIncrement(&comp, &index);
	while (index == comp->getChildNodes()->size())
	{
		if (memento.pop())
		{
			done = true;
			return 0;
		}
		memento.getAndIncrement(&comp, &index);
	}
	
	dom::NodeList* children = comp->getChildNodes();
	if (children->getChildAt(index)->hasChildNodes())
	{
		memento.push(children->getChildAt(index), -1);
	}
	return children->getChildAt(index);
}

bool NodeIter_Impl::isDone()
{
	return done;
}


void Memento::initialize(dom::Node* root)
{
	compositeArray[0] = root;
	indexArray[0] = 0;
	index = 0;
}

void Memento::push(dom::Node* comp, int indexInput)
{
	compositeArray[++index] = comp;
	indexArray[index] = indexInput;
}

bool Memento::pop()
{
	if (index == 0)
	{
		return true;
	}
	index--;
	return false;
}

void Memento::getAndIncrement(dom::Node** comp, int* indexInput)
{
	*comp = compositeArray[index];
	*indexInput = indexArray[index];
	indexArray[index]++;
}