/*
 * StaticTextField.h
 *
 *  Created on: Jul 10, 2015
 *      Author: michael
 */

#ifndef VIEW_FIELDS_STATICTEXTFIELD_H_
#define VIEW_FIELDS_STATICTEXTFIELD_H_

#include "AbstractField.h"
#include <Wt/WText>

namespace SiconfFields {

class StaticTextField: public AbstractField {
public:
	StaticTextField();
	void setMessage(std::string message);
	bool validate();
	inline Wt::WText* textField(){return _outputField;}

private:
	void _setTemplate();
	void _updateInvalidMessage(std::string message){};
	void _updateLabel(std::string label){_label->setText(label);};
	void reset(){_outputField->setText("");}

	Wt::WText* _outputField;
	Wt::WText* _label;
};

} /* namespace SiconfFields */

#endif /* VIEW_FIELDS_STATICTEXTFIELD_H_ */
