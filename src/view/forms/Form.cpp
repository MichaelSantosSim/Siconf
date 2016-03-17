/*
 * FieldSet.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: michael
 */

#include "Form.h"

namespace SiconfForms {

	Form::Form(std::string titulo, Wt::WContainerWidget* parent) : Wt::WTemplate(Wt::WString::tr("fieldset")) {
		if(parent){
			parent->addWidget(this);
		}
		_container = new Wt::WContainerWidget();
		_titulo = new Wt::WText(titulo);

		bindWidget("form-group", _container);
		bindWidget("title", _titulo);

	}

	void Form::reset(){
		for(auto i : _fields){
			i->reset();
		}

	}

	bool Form::validate(){
		bool result = true;

		for(auto i : _fields){
			if(!i->validate()){
				result = false;
			}
		}

		return result;
	}

	void Form::setTitle(std::string title){
		_titulo->setText(title);
	}

	void Form::addField(SiconfFields::AbstractField* field){
		_fields.push_back(field);
		_container->addWidget(field);
	}

} /* namespace SiconfForms */
