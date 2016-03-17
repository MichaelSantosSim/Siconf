/*
 * EnderecoForm.h
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_ENDERECOFORM_H_
#define VIEW_FORMS_ENDERECOFORM_H_

#include <Wt/WContainerWidget>
#include <Wt/WIntValidator>
#include <Wt/Dbo/Transaction>
#include <Wt/Dbo/Session>
#include "../../utils/SessionSetupHelper.hpp"
#include "../../model/models_defs.h"
#include "Form.h"

namespace SiconfForms {

class EnderecoForm: public Wt::WContainerWidget {
public:
	EnderecoForm();
	bool validate();
	Wt::Dbo::ptr<SiconfModel::Endereco> endereco();
	void fillForm(Wt::Dbo::ptr<SiconfModel::Endereco> endereco);
	bool updateEndereco(Wt::Dbo::ptr<SiconfModel::Endereco> endereco);
private:

	void _initialize();
	void _addToForm();
	void _setValidators();

	Wt::WValidator* _createIntValidator();

	Wt::Dbo::Session _dbSession;

	Form* _form;
	SiconfFields::LineField* _fieldCidade;
	SiconfFields::LineField* _fieldBairro;
	SiconfFields::LineField* _fieldRua;
	SiconfFields::LineField* _fieldNumero;
	SiconfFields::LineField* _fieldComplemento;

};

} /* namespace SiconfForms */

#endif /* VIEW_FORMS_ENDERECOFORM_H_ */
