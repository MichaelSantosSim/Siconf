/*
   * TextField.h
 *
 *  Created on: Jul 8, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_TEXTFIELD_H_
#define VIEW_FORMS_TEXTFIELD_H_

#include <Wt/WTemplate>

#include "AbstractField.h"
#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WValidator>

namespace SiconfFields {

class LineField: public AbstractField {
public:
	LineField();
	bool validate();
	inline std::string getInput() {return _fieldInput->text().toUTF8();}
	inline void setInput(std::string text){_fieldInput->setText(text);}
	void setValidator(Wt::WValidator* validator);
	void setEmptyValidator();

	void reset();

	Wt::WLineEdit* lineEdit(){return _fieldInput;}

private:

	void _updateLabel(std::string label);
	void _updateInvalidMessage(std::string message);

	void _setTemplate();

	Wt::WText* 		_fieldLabel;
	Wt::WText* 		_fieldInvalidMessage;
	Wt::WLineEdit*	_fieldInput;
};

} /* namespace SiconfUtils */

#endif /* VIEW_FORMS_TEXTFIELD_H_ */
