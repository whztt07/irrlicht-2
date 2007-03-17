#ifndef __C_GUI_ENUM_ATTRIBUTE_H_INCLUDED__
#define __C_GUI_ENUM_ATTRIBUTE_H_INCLUDED__

#include "CGUIAttribute.h"
#include "IGUIComboBox.h"
#include "IGUIEditBox.h"

namespace irr
{
namespace gui
{

	class CGUIEnumAttribute : public CGUIAttribute
	{
	public:
		//
		CGUIEnumAttribute(IGUIEnvironment* environment, IGUIElement *parent) :
			CGUIAttribute(environment, parent),	AttribComboBox(0), AttribEditBox(0)
		{

		}

		virtual ~CGUIEnumAttribute()
		{
			if (AttribComboBox)
				AttribComboBox->drop();
			if (AttribEditBox)
				AttribEditBox->drop();
		}

		// save the attribute and possibly post the event to its parent
		virtual void setAttrib(io::IAttributes *attribs, u32 attribIndex)
		{

			if (AttribComboBox)
			{
				AttribComboBox->remove();
				AttribComboBox->drop();
				AttribComboBox = 0;
			}

			if (AttribEditBox)
			{
				AttribEditBox->remove();
				AttribEditBox->drop();
				AttribEditBox = 0;
			}

			core::array<core::stringc> outLiterals;
			attribs->getAttributeEnumerationLiteralsOfEnumeration(attribIndex, outLiterals);

			core::rect<s32> r = getAbsolutePosition();
			core::rect<s32> r2(0, Environment->getSkin()->getFont()->getDimension(L"A").Height + 10, 
				r.getWidth() - 5, 
				Environment->getSkin()->getFont()->getDimension(L"A").Height*2 + 20 );

			if (outLiterals.size() > 0)
			{
				AttribComboBox = Environment->addComboBox(r2, this, -1);
				for (u32 i=0; i<outLiterals.size(); ++i)
					AttribComboBox->addItem( core::stringw(outLiterals[i].c_str()).c_str());

				AttribComboBox->setSelected( attribs->getAttributeAsInt(attribIndex) );

				AttribComboBox->grab();
				AttribComboBox->setSubElement(true);
				AttribComboBox->setAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
			}
			else
			{

				AttribEditBox = Environment->addEditBox(
						attribs->getAttributeAsStringW(attribIndex).c_str(),
						r2, true, this, -1);
				AttribEditBox->grab();
				AttribEditBox->setSubElement(true);
				AttribEditBox->setAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
			}
				
			CGUIAttribute::setAttrib(attribs, attribIndex);
		}

		//! save the attribute and possibly post the event to its parent
		virtual bool updateAttrib(bool sendEvent=true)
		{
			if (AttribComboBox)
				Attribs->setAttribute(Index, AttribComboBox->getText());
			else if (AttribEditBox)
				Attribs->setAttribute(Index, AttribEditBox->getText());

			return CGUIAttribute::updateAttrib(sendEvent);
		}

		//! this shoudln't be serialized, but this is included as it's an example
		virtual const c8* getTypeName() const { return "enum_attribute"; }

	private:
		IGUIComboBox*	AttribComboBox;
		IGUIEditBox*	AttribEditBox;
	};

} // namespace gui
} // namespace irr

#endif

