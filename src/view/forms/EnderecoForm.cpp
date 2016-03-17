/*
 * EnderecoForm.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#include "EnderecoForm.h"

namespace SiconfForms {

	EnderecoForm::EnderecoForm() : Wt::WContainerWidget() {


		SiconfUtils::SessionSetupHelper sessionSetup(SiconfUtils::SessionSetupHelper::DataBase::SQLITE3);
		sessionSetup(_dbSession);

		try{
			sessionSetup(_dbSession);
		}catch(Wt::Dbo::Exception& e){
			Wt::log("EnderecoForm") << e.what();
		}

		_initialize();
		_setValidators();
		_addToForm();
	}

	void EnderecoForm::fillForm(Wt::Dbo::ptr<SiconfModel::Endereco> endereco){
		_fieldCidade->setInput(endereco->cidade());
		_fieldBairro->setInput(endereco->bairro());
		_fieldRua->setInput(endereco->rua());
		_fieldNumero->setInput(std::to_string(endereco->numero()));
		_fieldComplemento->setInput(endereco->complemento());
	}

	bool EnderecoForm::updateEndereco(Wt::Dbo::ptr<SiconfModel::Endereco> endereco){
		if(validate()){
			endereco.modify()->definirCidade(_fieldCidade->getInput());
			endereco.modify()->definirBairro(_fieldBairro->getInput());
			endereco.modify()->definirRua(_fieldRua->getInput());
			endereco.modify()->definirNumero(std::atoi(_fieldNumero->getInput().c_str()));
			endereco.modify()->definirComplemento(_fieldComplemento->getInput());
			return true;
		}

		return false;
	}

	void EnderecoForm::_initialize(){

		_form = new Form();

		_fieldCidade = 		new SiconfFields::LineField();
		_fieldBairro = 		new SiconfFields::LineField();
		_fieldRua = 		new SiconfFields::LineField();
		_fieldNumero = 		new SiconfFields::LineField();
		_fieldComplemento = new SiconfFields::LineField();

		_fieldCidade->setLabel("Cidade");
		_fieldBairro->setLabel("Bairro");
		_fieldRua->setLabel("Rua");
		_fieldNumero->setLabel("Numero");
		_fieldComplemento->setLabel("Complemento");


	}

	void EnderecoForm::_setValidators(){

		_fieldCidade->setEmptyValidator();
		_fieldBairro->setEmptyValidator();
		_fieldRua->setEmptyValidator();

		// numero precisa de um validador diferente
		_fieldNumero->setValidator(_createIntValidator());

		// Complemento e opcional portanto nao precisa de um validator

		_fieldCidade->setInvalidMessage("");

	}

	Wt::WValidator* EnderecoForm::_createIntValidator(){
		Wt::WIntValidator* validator = new Wt::WIntValidator();
		validator->setBottom(0);
		validator->setMandatory(true);
		return validator;
	}

	void EnderecoForm::_addToForm(){

		_form->setTitle("Endereco");

		_form->addField(_fieldCidade);
		_form->addField(_fieldBairro);
		_form->addField(_fieldRua);
		_form->addField(_fieldNumero);
		_form->addField(_fieldComplemento);

		addWidget(_form);
	}

	bool EnderecoForm::validate(){
		return _form->validate();
	}

	Wt::Dbo::ptr<SiconfModel::Endereco> EnderecoForm::endereco(){

		Wt::Dbo::Transaction transaction(_dbSession);

		SiconfModel::Endereco* endereco = new SiconfModel::Endereco();
		endereco->definirCidade(_fieldCidade->getInput());
		endereco->definirBairro(_fieldBairro->getInput());
		endereco->definirRua(_fieldRua->getInput());
		endereco->definirNumero(atoi(_fieldNumero->getInput().c_str()));
		endereco->definirComplemento(_fieldComplemento->getInput());

		Wt::Dbo::ptr<SiconfModel::Endereco> end = _dbSession.add(endereco);

		transaction.commit();

		return end;
	}


} /* namespace SiconfForms */
