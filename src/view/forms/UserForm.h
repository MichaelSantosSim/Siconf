/*
 * UserForm.h
 *
 *  Created on: Jul 5, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_USERFORM_H_
#define VIEW_FORMS_USERFORM_H_

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WDateEdit>
#include <Wt/WValidator>
#include <Wt/WDateValidator>
#include <Wt/Dbo/Session>
#include <Wt/WLengthValidator>
#include <Wt/Dbo/Exception>
#include <Wt/WRegExpValidator>

#include "../fields/DateField.h"
#include "../fields/AbstractField.h"
#include "EnderecoForm.h"

#include "../../utils/SessionSetupHelper.hpp"
#include "../../model/models_defs.h"
#include "../fields/LineField.h"
#include "Form.h"

namespace SiconfForms {

class UserForm: public Wt::WContainerWidget {
public:
	UserForm(Wt::WContainerWidget* parent = 0);
	bool validate();
	Wt::Dbo::ptr<SiconfModel::Usuario> usuario();

	void fillForm(Wt::Dbo::ptr<SiconfModel::Usuario> usuario);
	bool updateUsuario(Wt::Dbo::ptr<SiconfModel::Usuario> usuario);

private:

	void _initialize();
	void _setStyle();
	void _buildFieldSet();
	void _setValidators();

	Wt::WValidator* _createEmailValidator();
	Wt::WValidator* _createDateValidator();

	EnderecoForm* _endereco;

	Form* _form;

	Wt::Dbo::Session       					 _dbSession;
	SiconfFields::LineField*				_fieldName;
	SiconfFields::LineField*				_fieldLastName;
	SiconfFields::LineField*				_fieldEmail;
	SiconfFields::DateField*				_fieldBirthDate;


};

} /* namespace SiconfForms */

#endif /* VIEW_FORMS_USERFORM_H_ */
