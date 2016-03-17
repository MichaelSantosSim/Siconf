/*
 * SpinBoxField.h
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#ifndef VIEW_FIELDS_SPINBOXFIELD_H_
#define VIEW_FIELDS_SPINBOXFIELD_H_

#include "AbstractField.h"
#include <Wt/WSpinBox>
#include <Wt/WText>

namespace SiconfFields {

class SpinBoxField: public AbstractField {
public:
	SpinBoxField();
	bool validate();
	inline int getInput() {return _fieldInput->value();}
	inline void setInput(int input){_fieldInput->setValue(input);}
	void setValidator(Wt::WValidator* validator);
	void setEmptyValidator();
	Wt::WSpinBox* spinBox(){return _fieldInput;};
	void reset();


private:

	void _updateLabel(std::string label);
	void _updateInvalidMessage(std::string message);

	void _setTemplate();

	Wt::WText* 		_fieldLabel;
	Wt::WText* 		_fieldInvalidMessage;
	Wt::WSpinBox*	_fieldInput;
};

} /* namespace SiconfFields */

#endif /* VIEW_FIELDS_SPINBOXFIELD_H_ */
