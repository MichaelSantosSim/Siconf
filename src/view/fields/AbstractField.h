/*
 * AbstractField.h
 *
 *  Created on: Jul 8, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_ABSTRACTFIELD_H_
#define VIEW_FORMS_ABSTRACTFIELD_H_

#include <Wt/WTemplate>
#include <Wt/WWidget>

namespace SiconfFields {

class AbstractField : public Wt::WTemplate {
public:
	AbstractField();
	virtual bool validate() = 0;
	virtual void reset() = 0;

	inline void setInvalidMessage(std::string message){_updateInvalidMessage(message); _invalidFieldMessage = message;}
	inline void setLabel(std::string label){_updateLabel(label); _label = label;}

	inline std::string invalidMessage() const {return _invalidFieldMessage;}
	inline std::string label() const {return _label;}


protected:

	/*
	 * Método para definir o template html que pode ser diferente dependendo do field
	 * Este deve ser chamado antes dos binds
	 * Ex Uso:
	 * 			void TextField::_setTemplate(){
	 *				setTemplateText(Wt::WString::tr("field"));
	 *			}
	 *
	 */
	virtual void _setTemplate() = 0;
	virtual void _updateInvalidMessage(std::string message) = 0;
	virtual void _updateLabel(std::string label) = 0;

	std::string _invalidFieldMessage;
	std::string _label;
};

} /* namespace SiconfUtils */

#endif /* VIEW_FORMS_ABSTRACTFIELD_H_ */
