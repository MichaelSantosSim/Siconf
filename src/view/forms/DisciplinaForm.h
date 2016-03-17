/*
 * DisciplinaForm.h
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_DISCIPLINAFORM_H_
#define VIEW_FORMS_DISCIPLINAFORM_H_

#include <Wt/WContainerWidget>
#include <Wt/WText>

#include "../fields/TextField.h"
#include "../fields/LineField.h"
#include "../fields/SpinBoxField.h"
#include "../../utils/SessionSetupHelper.hpp"
#include "../../model/models_defs.h"

#include "Form.h"

namespace SiconfForms {

class DisciplinaForm: public Wt::WContainerWidget {
public:
	DisciplinaForm();
	bool validate();
	void fillForm(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);
	bool updateDisciplina(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);
	Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina();

private:


	void _initialize();
	void _setValidators();
	void _addToForm();

	Wt::Dbo::Session _dbSession;

	Form* _form;

	SiconfFields::LineField* _fieldNome;
	SiconfFields::TextField* _fieldDescricao;
	SiconfFields::SpinBoxField* _fieldAulasPorSemana;
	SiconfFields::SpinBoxField* _fieldSerie;


};

} /* namespace SiconfForms */

#endif /* VIEW_FORMS_DISCIPLINAFORM_H_ */
