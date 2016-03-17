/*
 * DisciplinasList.h
 *
 *  Created on: Oct 10, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_LISTS_DISCIPLINASLIST_H_
#define SRC_VIEW_LISTS_DISCIPLINASLIST_H_

#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include <Wt/WSignal>
#include <Wt/WLink>
#include <Wt/WMessageBox>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WStackedWidget>
#include <iostream>
#include <Wt/WAnchor>
#include <Wt/Dbo/Session>
#include "../lists/AlunoList.h"
#include "../../model/models_defs.h"
#include "../../utils/Popup.h"
#include "../widgets/Anchor.h"
#include "../pages/DisciplinaManager.h"

namespace SiconfList {

class DisciplinasList: public Wt::WContainerWidget {
public:
	DisciplinasList(Wt::Dbo::ptr<SiconfModel::Professor> professor, Wt::Dbo::Session& session);

private:

	void _setHeader();
	Wt::WStackedWidget* _mainStack;
	std::vector<std::pair<Wt::Dbo::ptr<SiconfModel::Turma>, Wt::Dbo::ptr<SiconfModel::Disciplina>>> _rows;
	Wt::Dbo::Session& _dbSession;
	Wt::WTable* _list;
	std::map<SiconfModel::Turma::Turno, std::string> _turnos;
};

} /* namespace SiconfList */

#endif /* SRC_VIEW_LISTS_DISCIPLINASLIST_H_ */
