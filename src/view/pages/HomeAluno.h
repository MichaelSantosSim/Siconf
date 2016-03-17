/*
 * HomeAluno.h
 *
 *  Created on: Oct 25, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_PAGES_HOMEALUNO_H_
#define SRC_VIEW_PAGES_HOMEALUNO_H_

#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WResource>
#include <Wt/WImage>
#include <Wt/WBreak>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WDateTime>
#include <Wt/WAnchor>
#include <Wt/Dbo/Session>
#include "../../utils/Popup.h"
#include "../pages/AbstractPage.h"
#include "../../utils/PDFResource.h"
#include "../../model/models_defs.h"

namespace SiconfPage {

class HomeAluno : public AbstractPage {
public:
	HomeAluno(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Aluno> aluno);

private:
	void _setTable(Wt::WTable* table);
	float _getFrequecia(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);
	float _getMedia(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);
	Wt::WAnchor* _getShowAbout();
	Wt::Dbo::Session& _dbSession;
	Wt::WTable* _mainTable;
	Wt::Dbo::ptr<SiconfModel::Aluno> _aluno;
	Wt::WContainerWidget* _content;
};

}

#endif /* SRC_VIEW_PAGES_HOMEALUNO_H_ */
