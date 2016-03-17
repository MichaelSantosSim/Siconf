/*
 * DisciplinaForm.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#include "DisciplinaForm.h"

namespace SiconfForms {

DisciplinaForm::DisciplinaForm() : Wt::WContainerWidget(){

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

	addWidget(_form);

}

void DisciplinaForm::fillForm(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina){

}

bool DisciplinaForm::updateDisciplina(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina){

	if(validate()){

		return true;
	}

	return false;
}

Wt::Dbo::ptr<SiconfModel::Disciplina> DisciplinaForm::disciplina(){

	SiconfModel::Disciplina* disciplina = new SiconfModel::Disciplina();

	Wt::Dbo::Transaction transaction(_dbSession);
	return _dbSession.add(disciplina);
}

void DisciplinaForm::_setValidators(){
	_fieldNome->setEmptyValidator();
	_fieldAulasPorSemana->spinBox()->setMinimum(1);
	_fieldSerie->spinBox()->setMinimum(1);
	_fieldSerie->spinBox()->setMaximum(14);
}

bool DisciplinaForm::validate(){
	return _form->validate();
}

void DisciplinaForm::_addToForm(){
	_form->addField(_fieldNome);
	_form->addField(_fieldSerie);
	_form->addField(_fieldDescricao);
	_form->addField(_fieldAulasPorSemana);
}

void DisciplinaForm::_initialize(){

	using namespace SiconfFields;

	_form 					= new Form();
	_fieldNome				= new LineField();
	_fieldDescricao			= new TextField();
	_fieldAulasPorSemana 	= new SpinBoxField();
	_fieldSerie				= new SpinBoxField();

	_form->setTitle("Disciplina	");

	_fieldSerie->spinBox()->setValue(1);
	_fieldAulasPorSemana->spinBox()->setValue(1);
	_fieldAulasPorSemana->setInvalidMessage("Deve haver no minimo uma aula por semana");

	_fieldNome->setLabel("Nome da Disciplina");
	_fieldSerie->setLabel("Serie");
	_fieldDescricao->setLabel("Descricao");
	_fieldAulasPorSemana->setLabel("Aulas por semana");
}


} /* namespace SiconfForms */
