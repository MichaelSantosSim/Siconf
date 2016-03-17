/*
 * AvaliacaoForm.h
 *
 *  Created on: Oct 19, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_FORMS_AVALIACAOFORM_H_
#define SRC_VIEW_FORMS_AVALIACAOFORM_H_

#include "../../model/models_defs.h"
#include "../fields/LineField.h"
#include "../../utils/Popup.h"
#include <Wt/WLabel>
#include <Wt/WContainerWidget>
#include <Wt/Dbo/Session>
#include <Wt/WDoubleSpinBox>
#include <Wt/WDoubleValidator>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WBreak>
#include <map>

namespace SiconfForms {

class AvaliacaoForm: public Wt::WContainerWidget {
public:
	AvaliacaoForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);
	AvaliacaoForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina, Wt::Dbo::ptr<SiconfModel::Avaliacao> avaliacao);
	bool validate();
	void updateForm(Wt::Dbo::ptr<SiconfModel::Avaliacao> avaliacao);


private:
	void _initialize();
	void _fillForm();
	void _setValidators();
	void addToForm();
	void _save();

	Wt::WTable* _list;
	Wt::Dbo::Session& _dbSession;
	Wt::Dbo::ptr<SiconfModel::Disciplina> _disciplina;
	Wt::Dbo::ptr<SiconfModel::Avaliacao> _avaliacao;
	std::vector<std::pair<Wt::WDoubleSpinBox*, Wt::Dbo::ptr<SiconfModel::Aluno>>> _sortList;
	Wt::WLineEdit* _nome;

};

} /* namespace SiconfForms */

#endif /* SRC_VIEW_FORMS_AVALIACAOFORM_H_ */
