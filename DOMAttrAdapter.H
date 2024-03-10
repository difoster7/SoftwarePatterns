#ifndef DOMAttrAdapter_H
#define DOMAttrAdapter_H

#include "Attr.H"
#include "DOMNodeAdapter.H"

namespace XERCES
{
	// DOMAttr is a target in the adapter pattern
	class DOMAttr {};	// empty class to make inheritance work

	// DOMAttrAdapter is an adapter in the adapter pattern
	class DOMAttrAdapter : public virtual DOMAttr, DOMNodeAdapter
	{
	private:
		dom::Attr* attrRef;

	protected:

	public:
		DOMAttrAdapter() {};
		DOMAttrAdapter(dom::Attr* attr) { attrRef = attr; };

		virtual ~DOMAttrAdapter() {};
	};
};
#endif // DOMAttrAdapter_H