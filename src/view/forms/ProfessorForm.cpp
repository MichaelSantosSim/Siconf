/*
 * ProfessorForm.cpp
 *
 *  Created on: Jul 10, 2015
 *      Author: michael
 */

#include "ProfessorForm.h"
#include "../fields/DateField.h"

namespace SiconfForms {

	ProfessorForm::ProfessorForm() {

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

	void ProfessorForm::_initialize(){

		_userForm = new UserForm;

		_form = new Form();
		_form->setTitle("Professor");

		_fieldMatricula = new SiconfFields::StaticTextField();
		_fieldMatricula->setLabel("Matricula");
		_fieldMatricula->setMessage(std::to_string(_findMatricula()));

	}

	void ProfessorForm::_setValidators(){

	}

	void ProfessorForm::_addToForm(){
		addWidget(_userForm);
		addWidget(_form);

		_form->addField(_fieldMatricula );

		SiconfFields::ListField<int>* list = new SiconfFields::ListField<int>();
		list->setHeader("Materias");
		list->setLabel("Materias Lecionadas");
		_form->addField(list);

	}

	int ProfessorForm::_findMatricula(){
		Wt::Dbo::Transaction transaction(_dbSession);

		Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Professor>> professores = _dbSession.find<SiconfModel::Professor>();

		int matricula = professores.size();

		Wt::Dbo::ptr<SiconfModel::Professor> professor = _dbSession.find<SiconfModel::Professor>().where("id = ?").bind(matricula);

		while(professor){
			matricula++;
			professor = _dbSession.find<SiconfModel::Professor>().where("id = ?").bind(matricula);
		}
		return matricula;
	}


} /* namespace SiconfForms */
