/*
 * TextField.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#include "TextField.h"

namespace SiconfFields {

	TextField::TextField() : AbstractField(),
			_fieldLabel(new Wt::WText("Campo")),
			_fieldInvalidMessage(new Wt::WText("Dados incorretos")),
			_fieldInput(new Wt::WTextEdit()){

		_setTemplate();
		_fieldInput->setStyleClass("form-control");
		_fieldInvalidMessage->hide();

		bindWidget("label", _fieldLabel);
		bindWidget("info", _fieldInvalidMessage);
		bindWidget("field", _fieldInput);

	}

	void TextField::_setTemplate(){
		setTemplateText(Wt::WString::tr("field"));
	}

	void TextField::reset(){
		_fieldInput->setText("");
	}

	void TextField::setEmptyValidator(){
		Wt::WValidator* validator = new Wt::WValidator();
		validator->inputFilter();
		validator->setMandatory(true);
		_fieldInput->setValidator(validator);
	}

	void TextField::setValidator(Wt::WValidator* validator){
		_fieldInput->setValidator(validator);
	}

	bool TextField::validate(){

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

	void TextField::_updateInvalidMessage(std::string message){
		_fieldInvalidMessage->setText(message);
	}

	void TextField::_updateLabel(std::string label){
		_fieldLabel->setText(label);
	}

} /* namespace SiconfFields */
