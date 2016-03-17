/*
 * SpinBoxField.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#include "SpinBoxField.h"

namespace SiconfFields {

SpinBoxField::SpinBoxField() : AbstractField(),
		_fieldLabel(new Wt::WText("Campo")),
		_fieldInvalidMessage(new Wt::WText("Dados incorretos")),
		_fieldInput(new Wt::WSpinBox()){

	setEmptyValidator();
	_fieldInput->setMinimum(0);
	_fieldInput->setWidth(100);

	setInvalidMessage("Selecione/Digite um numero valido");

	_setTemplate();
	_fieldInput->setStyleClass("form-control");
	_fieldInvalidMessage->hide();

	bindWidget("label", _fieldLabel);
	bindWidget("info", _fieldInvalidMessage);
	bindWidget("field", _fieldInput);

}

void SpinBoxField::reset(){
	_fieldInput->setValue(0);
}

void SpinBoxField::_setTemplate(){
	setTemplateText(Wt::WString::tr("field"));
}

void SpinBoxField::setEmptyValidator(){
	Wt::WValidator* validator = new Wt::WValidator();
	validator->inputFilter();
	validator->setMandatory(true);
	_fieldInput->setValidator(validator);
}


void SpinBoxField::setValidator(Wt::WValidator* validator){
	_fieldInput->setValidator(validator);
}

bool SpinBoxField::validate(){

	if(_fieldInput->validator() == 0){
		return true;
	}else{

		Wt::WValidator::State result = _fieldInput->validate();

		if(result == Wt::WValidator::Valid){
			_fieldInvalidMessage->hide();
			return true;
		}else{

			if(result == Wt::WValidator::InvalidEmpty){
				_fieldInvalidMessage->setText("Este campo deve ser preenchido!");
				_fieldInvalidMessage->show();
			}else{
				_fieldInvalidMessage->setText(_invalidFieldMessage);
				_fieldInvalidMessage->show();
			}
		}
	}

	return false;
}

void SpinBoxField::_updateInvalidMessage(std::string message){
	_fieldInvalidMessage->setText(message);
}

void SpinBoxField::_updateLabel(std::string label){
	_fieldLabel->setText(label);
}
} /* namespace SiconfFields */
