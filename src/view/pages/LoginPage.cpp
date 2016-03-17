/*
 * LoginPage.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: michael
 */

#include "LoginPage.h"

namespace SiconfPage {

LoginPage::LoginPage(SiconfUtils::PageNavigator* navigator, Wt::Dbo::Session& dbSession) :
		AbstractPage("login"),_navigator(navigator), _dbSession(dbSession)
		{
	_login = new SiconfUtils::Login(_dbSession);
	_initialize();

	Wt::WTemplate* t = new Wt::WTemplate(Wt::WString::tr("login_page"), this);

	t->bindWidget("user-name", _userName);
	t->bindWidget("password", _password);
	t->bindWidget("enter", _enter);
	_userName->setFocus();
}

void LoginPage::_initialize(){
	Wt::Dbo::Transaction transaction(_dbSession);
	_userName = new Wt::WLineEdit();
	_userName->setStyleClass("form-control");
	_password = new Wt::WLineEdit();
	_password->setStyleClass("form-control");
	_password->setEchoMode(Wt::WLineEdit::EchoMode::Password);
	_password->setAttributeValue("	", "");
	_enter = new Wt::WPushButton("Entrar");
	_enter->setStyleClass("btn btn-primary");


	_enter->clicked().connect(std::bind([&](){
		Wt::Dbo::Transaction transaction(_dbSession);
		Wt::Dbo::ptr<SiconfModel::Usuario> usuario = _login->verifyLogin(_userName->text().toUTF8());
		if(usuario){
			if(_login->verifyPassword(usuario, _password->text().toUTF8())){
				_setPage(usuario);
			}else{
				new SiconfUtils::Popup("Senha incorreta", "Atencao");
			}
		}else{
			new SiconfUtils::Popup("Usuario Incorreto", "Atencao");
		}
	}));
}

void LoginPage::_setPage(Wt::Dbo::ptr<SiconfModel::Usuario> usuario){
	Wt::Dbo::Transaction transaction(_dbSession);

	typedef SiconfModel::Usuario SU;
	SU::TipoUsuario tipo = usuario->tipoUsuario();

	if(tipo == SU::_Professor){

		Wt::Dbo::ptr<SiconfModel::Professor> professor = _login->getProfessor(usuario);
		if(professor){
			_navigator->addPage(new HomeProfessor(_dbSession, professor));
			_navigator->setInternalPath("/home_professor/");
		}else{
			new SiconfUtils::Popup("Erro ao recuperar dados do banco", "Atencao");
		}


	}else if(tipo == SU::_Aluno){

		Wt::Dbo::ptr<SiconfModel::Aluno> aluno = _login->getAluno(usuario);
		if(aluno){
				_navigator->addPage(new HomeAluno(_dbSession, aluno));
				_navigator->setInternalPath("/home_aluno/");

		}else{
			new SiconfUtils::Popup("Erro ao recuperar dados do banco, aluno nao encontrado", "Atencao");
		}

	}else if(tipo == SU::_Administrador){

		new SiconfUtils::Popup("Bem vindo, administrador", "Atencao");

	}else{
		new SiconfUtils::Popup("Erro ao recuperar dados do banco, tipo usuario = " + tipo, "Atencao");
	}
}

} /* namespace SiconfPage */
