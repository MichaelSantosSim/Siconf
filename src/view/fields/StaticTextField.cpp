/*
 * StaticTextField.cpp
 *
 *  Created on: Jul 10, 2015
 *      Author: michael
 */

#include "StaticTextField.h"

namespace SiconfFields  {

StaticTextField::StaticTextField() : AbstractField(),
		_outputField(new Wt::WText("Texto")),
		_label(new Wt::WText("Campo")){
	_setTemplate();
		bindWidget("label", _label);
		bindEmpty("info");
		bindWidget("field", _outputField);

	}

	void StaticTextField::setMessage(std::string message){
		_outputField->setText(message);
	}

	void StaticTextField::_setTemplate(){
		setTemplateText(Wt::WString::tr("field"));
	}

	bool StaticTextField::validate(){
		return true;
	}

} /* namespace SiconfFields */
