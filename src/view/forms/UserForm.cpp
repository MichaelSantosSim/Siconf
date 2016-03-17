/*
 * UserForm.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: michael
 */

#include "UserForm.h"
#include <Wt/WPushButton>
#include <Wt/WMessageBox>

namespace SiconfForms {

	UserForm::UserForm(Wt::WContainerWidget* parent) {

		SiconfUtils::SessionSetupHelper sessionSetup(SiconfUtils::SessionSetupHelper::DataBase::SQLITE3);
		sessionSetup(_dbSession);

		try{
			sessionSetup(_dbSession);
		}catch(Wt::Dbo::Exception& e){
			Wt::log("UserForm") << e.what();
		}

		_initialize();
		_buildFieldSet();
		_setValidators();
		_setStyle();
		addWidget(_endereco);

	}

	void UserForm::fillForm(Wt::Dbo::ptr<SiconfModel::Usuario> usuario){

		_fieldName->setInput(usuario->nome());
		_fieldLastName->setInput(usuario->sobrenome());
		_fieldEmail->setInput(usuario->email());
		_fieldBirthDate->setInput(usuario->dataNascimento());

		if(usuario->endereco()){
			_endereco->fillForm(usuario->endereco());
		}

	}

	bool UserForm::updateUsuario(Wt::Dbo::ptr<SiconfModel::Usuario> usuario){

		if(validate()){
			usuario.modify()->definirNome(_fieldName->getInput());
			usuario.modify()->definirSobrenome(_fieldLastName->getInput());
			usuario.modify()->definirEmail(_fieldEmail->getInput());
			usuario.modify()->definirDataNascimento(_fieldBirthDate->getInput());
			usuario.modify()->definirEndereco(_endereco->endereco());
			return true;
		}

		return false;
	}

	Wt::Dbo::ptr<SiconfModel::Usuario> UserForm::usuario(){

		SiconfModel::Usuario* usuario = new SiconfModel::Usuario();

		usuario->definirNome(_fieldName->getInput());
		usuario->definirSobrenome(_fieldLastName->getInput());
		usuario->definirEmail(_fieldEmail->getInput());
		usuario->definirDataNascimento(_fieldBirthDate->getInput());

		Wt::Dbo::Transaction transaction(_dbSession);

		Wt::Dbo::ptr<SiconfModel::Usuario> user = _dbSession.add(usuario);



		user.modify()->definirEndereco(_endereco->endereco());
		transaction.commit();

		return user;
	}


	bool UserForm::validate(){
		// o operador && nao verifica a segunda condicao se a primeira for false
		// ja que precisamos que o endereco exiba as mensagens de erro isso e feito
		// separando em duas variaveis e depois verificando a conficao

		bool usuario = _form->validate();
		bool endereco = _endereco->validate();

		return (usuario && endereco);
	}



	void UserForm::_setValidators(){

		_fieldName->setEmptyValidator();
		_fieldLastName->setEmptyValidator();

		// email e data precisam de um validador diferente
		_fieldEmail->setValidator(_createEmailValidator());
		_fieldBirthDate->setValidator(_createDateValidator());


	}

	void UserForm::_buildFieldSet(){

		_fieldName->setInvalidMessage("Este campo nao pode estar vazio");
		_fieldLastName->setInvalidMessage("Este campo nao pode estar vazio");
		_fieldEmail->setInvalidMessage("Digite um email valido");
		_fieldBirthDate->setInvalidMessage("Selecione uma data de nascimento valida");

		_fieldName->setLabel("Nome");
		_fieldLastName->setLabel("Sobrenome");
		_fieldEmail->setLabel("email");
		_fieldBirthDate->setLabel("Data de Nascimento");


		_form->addField(_fieldName);
		_form->addField(_fieldLastName);
		_form->addField(_fieldEmail);
		_form->addField(_fieldBirthDate);

	}


	Wt::WValidator* UserForm::_createEmailValidator(){
		Wt::WRegExpValidator *validator = new Wt::WRegExpValidator("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}");
		validator->setMandatory(true);
		return validator;
	}

	Wt::WValidator* UserForm::_createDateValidator(){
	      Wt::WDateValidator *v = new Wt::WDateValidator();
	      v->setBottom(Wt::WDate(1900, 1, 1));
	      v->setTop(Wt::WDate::currentDate());
	      v->setFormat("dd/MM/yyyy");
	      v->setMandatory(true);
	      return v;
	}

	void UserForm::_initialize(){

		_endereco = 		new EnderecoForm();

		_fieldName = 		new SiconfFields::LineField();
		_fieldLastName = 	new SiconfFields::LineField();
		_fieldEmail = 		new SiconfFields::LineField();
		_fieldBirthDate = 		new SiconfFields::DateField();
		_form = 			new Form("Usuario", this);
	}

	void UserForm::_setStyle(){
		setMargin(Wt::WLength::Auto, Wt::Left | Wt::Right);
	}
} /* namespace SiconfForms */
