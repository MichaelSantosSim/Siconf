/*
 * AvaliacaoManager.h
 *
 *  Created on: Oct 25, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_PAGES_AVALIACAOMANAGER_H_
#define SRC_VIEW_PAGES_AVALIACAOMANAGER_H_

#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WAnchor>
#include <Wt/WPushButton>
#include <Wt/Dbo/Session>
#include "../../utils/Popup.h"
#include "../widgets/Anchor.h"
#include "../forms/AvaliacaoForm.h"

namespace SiconfPages {

class AvaliacaoManager: public Wt::WContainerWidget {
public:
	AvaliacaoManager(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);

private:

	void _backToMain();
	void _setTable();
	void _apagarDisciplina(Wt::Dbo::ptr<SiconfModel::Avaliacao> avaliacao);

	Wt::Dbo::Session& 						_dbSession;
	Wt::Dbo::ptr<SiconfModel::Disciplina> 	_disciplina;
	Wt::WStackedWidget* 					_mainStack;
	Wt::WContainerWidget* 					_mainPage;
	Wt::WTable* 							_disciplinaTable;
	Wt::WPushButton* _adicionarAvaliacao;

};

} /* namespace SiconfPages */

#endif /* SRC_VIEW_PAGES_AVALIACAOMANAGER_H_ */
