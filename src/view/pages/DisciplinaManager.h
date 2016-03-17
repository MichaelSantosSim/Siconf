/*
 * DisciplinaManager.h
 *
 *  Created on: Oct 15, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_PAGES_DISCIPLINAMANAGER_H_
#define SRC_VIEW_PAGES_DISCIPLINAMANAGER_H_

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/Dbo/Session>
#include <Wt/WStackedWidget>
#include <boost/signals/connection.hpp>
#include <Wt/WDate>
#include "../../utils/Popup.h"
#include "../../model/models_defs.h"
#include "../lists/AlunoList.h"
#include "../forms/AvaliacaoForm.h"
#include "../forms/DisciplinaForm.h"
#include "../forms/ChamadaForm.h"
#include "../pages/AvaliacaoManager.h"

namespace SiconfPage {

class DisciplinaManager: public Wt::WContainerWidget {
public:
	DisciplinaManager(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);

private:

	void showAdicionarAvaliacao();
	void showFazerChamada();
	void showRefazerChamada();
	Wt::WStackedWidget* 					_mainStack;
	Wt::WContainerWidget* 					_mainContainer;
	SiconfList::AlunoList* 					_alunoList;
	Wt::WPushButton* 						_gerenciarAvaliacoes;
	Wt::WPushButton*						_fazerChamada;
	Wt::Dbo::Session& 						_dbSession;
	Wt::Dbo::ptr<SiconfModel::Disciplina> 	_disciplina;

	boost::signals::connection 				fazerChamadaConnection;
};

} /* namespace SiconfPage */

#endif /* SRC_VIEW_PAGES_DISCIPLINAMANAGER_H_ */
