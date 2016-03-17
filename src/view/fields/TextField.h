/*
 * TextField.h
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#ifndef VIEW_FIELDS_TEXTFIELD_H_
#define VIEW_FIELDS_TEXTFIELD_H_

#include "AbstractField.h"
#include <Wt/WText>
#include <Wt/WValidator>
#include <Wt/WTextEdit>

namespace SiconfFields {

class TextField: public AbstractField {
public:
	TextField();
	bool validate();
	inline std::string getInput() {return _fieldInput->text().toUTF8();}
	void setInput(std::string input){_fieldInput->setText(input);}
	void setValidator(Wt::WValidator* validator);
	void setEmptyValidator();
	Wt::WTextEdit* textEdit(){return _fieldInput;}
	void reset();

private:

	void _updateLabel(std::string label);
	void _updateInvalidMessage(std::string message);

	void _setTemplate();

	Wt::WText* 		_fieldLabel;
	Wt::WText* 		_fieldInvalidMessage;
	Wt::WTextEdit*	_fieldInput;
};

} /* namespace SiconfFields */

#endif /* VIEW_FIELDS_TEXTFIELD_H_ */
