/*
 * DateField.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: michael
 */

#include "DateField.h"

namespace SiconfFields {

DateField::DateField() :	AbstractField(),
							_fieldLabel(new Wt::WText("Data")),
							_fieldInvalidMessage(new Wt::WText("Escolha uma data valida!")),
							_fieldInput(new Wt::WDateEdit()){

	_fieldInvalidMessage->hide();
	_fieldInput->setStyleClass("form-control");

	_setTemplate();
	bindWidget("label", _fieldLabel);
	bindWidget("field", _fieldInput);
	bindWidget("info", _fieldInvalidMessage);
}

void DateField::reset(){
	_fieldInput->setText("");
}

void DateField::_setTemplate(){
	setTemplateText(Wt::WString::tr("field"));
}

bool DateField::validate(){

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

Wt::WDate DateField::getInput(){
	return _fieldInput->date();
}

void DateField::setValidator(Wt::WValidator* validator){
	_fieldInput->setValidator(validator);
}

void DateField::_updateInvalidMessage(std::string message){
	_fieldInvalidMessage->setText(message);
}

void DateField::_updateLabel(std::string label){
	_fieldLabel->setText(label);
}


} /* namespace SiconfUtils */
