#ifndef DOMTextAdapter_H
#define DOMTextAdapter_H

#include "Text.H"
#include "DOMNodeAdapter.H"

namespace XERCES
{
	// DOMText is a target in the adapter pattern
	class DOMText : public virtual DOMNode {};	// empty class to make inheritance work

	// DOMTextAdapter is an adapter in the adapter pattern
	class DOMTextAdapter : public virtual DOMText, DOMNodeAdapter
	{
	private:
		dom::Text* textRef;

	protected:

	public:
		DOMTextAdapter() {};
		DOMTextAdapter(dom::Text* text) { textRef = text; };

		virtual ~DOMTextAdapter() {};
	};
};
#endif // DOMTextAdapter_H