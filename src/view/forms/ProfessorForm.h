/*
 * ProfessorForm.h
 *
 *  Created on: Jul 10, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_PROFESSORFORM_H_
#define VIEW_FORMS_PROFESSORFORM_H_

#include <Wt/WContainerWidget>
#include <Wt/WText>

#include "../fields/TextField.h"
#include "../fields/LineField.h"
#include "../fields/StaticTextField.h"
#include "../fields/ComboField.h"
#include "../fields/ListField.h"
#include "UserForm.h"

#include "../../utils/SessionSetupHelper.hpp"
#include "../../model/models_defs.h"

#include "Form.h"

namespace SiconfForms {

class ProfessorForm: public Wt::WContainerWidget {
public:
	ProfessorForm();
	bool validate();
	void fillForm(Wt::Dbo::ptr<SiconfModel::Professor> professor);
	bool updateProfessor(Wt::Dbo::ptr<SiconfModel::Professor> professor);

	Wt::Dbo::ptr<SiconfModel::Professor> professor();

private:

	int _findMatricula();
	void _initialize();
	void _setValidators();
	void _addToForm();

	Wt::Dbo::Session _dbSession;

	Form* _form;
	UserForm* _userForm;

	SiconfFields::StaticTextField* _fieldMatricula;
	SiconfFields::ComboField<SiconfModel::Disciplina>* fieldDisciplina;

	std::vector<SiconfFields::ComboField<SiconfModel::Disciplina>*> _disciplinas;
};

} /* namespace SiconfForms */

#endif /* VIEW_FORMS_PROFESSORFORM_H_ */
