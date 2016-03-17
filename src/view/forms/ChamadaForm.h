/*
 * ChamadaForm.h
 *
 *  Created on: Oct 22, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_FORMS_CHAMADAFORM_H_
#define SRC_VIEW_FORMS_CHAMADAFORM_H_

#include <Wt/WContainerWidget>
#include <Wt/Dbo/Session>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WTableView>
#include <Wt/WCheckBox>
#include <Wt/WDialog>
#include <map>
#include "../../utils/Popup.h"
#include "../../model/models_defs.h"

namespace SiconfForms {

class ChamadaForm: public Wt::WContainerWidget {
public:
	ChamadaForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);
	ChamadaForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina, Wt::Dbo::ptr<SiconfModel::Aula> aula);

private:

	void _save();
	void _initialize();
	void _percorrerChamada();
	Wt::Dbo::Session& _dbSession;
	Wt::Dbo::ptr<SiconfModel::Disciplina> _disciplina;
	Wt::WTable* _list;
	Wt::Dbo::ptr<SiconfModel::Aula> _aula;

	std::vector<std::pair<Wt::WCheckBox*, Wt::Dbo::ptr<SiconfModel::Aluno>>> sortList;
};

class AutoChamada: public Wt::WDialog{
public:
	AutoChamada(Wt::Dbo::Session& dbSession, std::vector<std::pair<Wt::WCheckBox*, Wt::Dbo::ptr<SiconfModel::Aluno>>> list);
private:

	void _presenteClicked();
	void _ausenteClicked();
	void _anteriorClicked();
	void _cancelClicked();


	Wt::Dbo::Session& _dbSession;
	std::vector<std::pair<Wt::WCheckBox*, Wt::Dbo::ptr<SiconfModel::Aluno>>> _list;
	unsigned int index;

	Wt::WPushButton* _presente;
	Wt::WPushButton* _ausente;
	Wt::WPushButton* _anterior;
	Wt::WPushButton* _cancelar;

	Wt::WText* _name;
};

} /* namespace SiconfForms */

#endif /* SRC_VIEW_FORMS_CHAMADAFORM_H_ */
