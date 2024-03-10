#ifndef DOMElementAdapter_H
#define DOMElementAdapter_H

#include "Element.H"
#include "DOMNodeAdapter.H"

namespace XERCES
{
	// DOMElement is a target in the adapter pattern
	class DOMElement {};	// Empty class to make inheritance work

	// DOMElementAdapter is an adapter in the adapter pattern
	class DOMElementAdapter : public virtual DOMElement, DOMNodeAdapter
	{
	private:
		dom::Element* eleRef;

	protected:

	public:
		DOMElementAdapter() {};
		DOMElementAdapter(dom::Element* ele) { eleRef = ele; };

		virtual ~DOMElementAdapter() {};
	};
};
#endif // DOMElementAdapter_H