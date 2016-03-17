/*
 * DateField.h
 *
 *  Created on: Jul 8, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_DATEFIELD_H_
#define VIEW_FORMS_DATEFIELD_H_

#include <Wt/WDateEdit>
#include <Wt/WTemplate>
#include <Wt/WText>
#include "AbstractField.h"

namespace SiconfFields {

class DateField : public AbstractField {
public:
	DateField();
	bool validate();
	void setValidator(Wt::WValidator* validator);
	Wt::WDate getInput();
	inline void setInput(Wt::WDate date){_fieldInput->setDate(date);}

	Wt::WDateEdit* dateField(){return _fieldInput;}
	void reset();

private:

	Wt::WText* 		_fieldLabel;
	Wt::WText* 		_fieldInvalidMessage;
	Wt::WDateEdit*	_fieldInput;

	void _setTemplate();
	void _updateInvalidMessage(std::string message);
	void _updateLabel(std::string label);

};

} /* namespace SiconfUtils */

#endif /* VIEW_FORMS_DATEFIELD_H_ */
