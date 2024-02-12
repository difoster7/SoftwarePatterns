#ifndef NODELIST_H
#define NODELIST_H

#include <list>

namespace dom
{
	class Node;

	class NodeList : public std::list<Node *>
	{
	public:
		virtual iterator	find(Node *n)
		{
			iterator	i;

			for (i = begin(); i != end(); i++)
				if (*i.operator->() == n)
					break;

			return i;
		}
		
		virtual Node* getChildAt(int index)
		{
			iterator i = begin();
			int indexCounter = 0;
			while (indexCounter < index && i != end())
			{
				indexCounter++;
				i++;
			}
			if (i == end())
			{
				printf("Error index out of bounds.\n");
				return 0;
			}
			return *i;
		}
	};
};

#endif // NODELIST_H
