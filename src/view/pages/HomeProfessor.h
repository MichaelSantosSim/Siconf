/*
 * HomeProfessor.h
 *
 *  Created on: Aug 23, 2015
 *      Author: michael
 */

#ifndef VIEW_PAGES_HOMEPROFESSOR_H_
#define VIEW_PAGES_HOMEPROFESSOR_H_

#include "AbstractPage.h"
#include "../lists/DisciplinasList.h"
#include "../lists/TurmaList.h"
#include "../../model/models_defs.h"
#include "../../utils/SessionSetupHelper.hpp"
#include "../../utils/Popup.h"
#include <Wt/Dbo/Session>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTemplate>
#include <Wt/WImage>
#include <Wt/WStackedWidget>


namespace SiconfPage {

class HomeProfessor: public AbstractPage {
public:
	HomeProfessor(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Professor> professor);
private:

	Wt::WAnchor* _getDisciplinaListAnchor();
	Wt::WAnchor* _getDadosProfessorAnchor();
	Wt::WAnchor* _getTurmaListAnchor();
	Wt::WAnchor* _getShowAbout();
	Wt::Dbo::ptr<SiconfModel::Professor> _professor;
	Wt::Dbo::Session& _dbSession;
	Wt::WStackedWidget* _mainStack;
	Wt::WText* _currentMenu;

	SiconfList::DisciplinasList* _disciplinaList;
	SiconfList::TurmaList* _turmaList;

};

} /* namespace SiconfPage */

#endif /* VIEW_PAGES_HOMEPROFESSOR_H_ */
