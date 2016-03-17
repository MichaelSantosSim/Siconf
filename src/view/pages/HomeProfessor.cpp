/*
 * HomeProfessor.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: michael
 */

#include "HomeProfessor.h"

namespace SiconfPage {

HomeProfessor::HomeProfessor(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Professor> professor) :
		AbstractPage("/home_professor/"), _professor(professor), _dbSession(dbSession), _mainStack(new Wt::WStackedWidget()), _currentMenu(new Wt::WText("Disciplinas")) {

	Wt::WTemplate* t = new Wt::WTemplate(Wt::WString::tr("home_professor"), this);
	Wt::Dbo::Transaction transaction(_dbSession);

	_disciplinaList = new SiconfList::DisciplinasList(_professor, _dbSession);
	_turmaList = new SiconfList::TurmaList(_dbSession, _professor);
	_mainStack->addWidget(_disciplinaList);
	_mainStack->addWidget(_turmaList);

	t->bindWidget("dados_professor", _getDadosProfessorAnchor());
	t->bindWidget("disciplinas", _getDisciplinaListAnchor());
	t->bindWidget("turmas", _getTurmaListAnchor());
	t->bindWidget("main-stack", _mainStack);
	t->bindWidget("currentMenu", _currentMenu);
	t->bindWidget("about", _getShowAbout());

}
Wt::WAnchor* HomeProfessor::_getTurmaListAnchor(){
	Wt::WAnchor* anchor = new Wt::WAnchor();
	anchor->addStyleClass("Wt-Anchor");
	anchor->setText("Turmas");
	anchor->clicked().connect(std::bind([=](){
		_currentMenu->setText("Turmas");
		_mainStack->setCurrentWidget(_turmaList);
	}));
	return anchor;
}

Wt::WAnchor* HomeProfessor::_getDisciplinaListAnchor(){
	Wt::WAnchor* anchor = new Wt::WAnchor();
	anchor->addStyleClass("Wt-Anchor");
	anchor->setText("Home Professor");

	anchor->clicked().connect(std::bind([=](){
		_mainStack->setCurrentWidget(_disciplinaList);
		_currentMenu->setText("Home Professor");
	}));
	return anchor;
}

Wt::WAnchor* HomeProfessor::_getDadosProfessorAnchor(){
	Wt::WAnchor* anchor = new Wt::WAnchor();
		anchor->setText("Dados do Professor");
		anchor->addStyleClass("Wt-Anchor");

		anchor->clicked().connect(std::bind([=](){
			Wt::Dbo::Transaction transaction(_dbSession);
			Wt::WContainerWidget* container = new Wt::WContainerWidget();

			Wt::WTemplate* t = new Wt::WTemplate(Wt::WTemplate::tr("dados_professor"), container);

			t->bindWidget("nome", new Wt::WText(_professor->usuario()->nome() + " " + _professor->usuario()->sobrenome()));
			t->bindWidget("email", new Wt::WText(_professor->usuario()->email()));
			t->bindWidget("login", new Wt::WText(_professor->usuario()->login()));

			Wt::WTable* table = new Wt::WTable();
			table->setWidth(Wt::WLength("100%"));

			for(auto i : _professor->disciplinas()){
				new Wt::WText(i->nome(), table->elementAt(table->rowCount(), 0));
			}

			t->bindWidget("materias", table);
			t->bindWidget("titulo", new Wt::WText("Dados do Professor"));
			SiconfUtils::Popup* popup =  new SiconfUtils::Popup(container, "");
			popup->setWidth(500);
		}));

		return anchor;
}

Wt::WAnchor* HomeProfessor::_getShowAbout(){
	Wt::WAnchor* anchor = new Wt::WAnchor();
	anchor->setText("Sobre");
	anchor->addStyleClass("Wt-Anchor");
	anchor->clicked().connect(std::bind([=](){
		SiconfUtils::Popup* popup =  new SiconfUtils::Popup( "Tower Systens LTDA", "Siconf - Sistema de Controle de Notas e Frequencia");
		new Wt::WBreak(popup->contents());
		Wt::WImage* image = new Wt::WImage(Wt::WLink("img/tower.png"), popup->contents());
		image->resize(50, 70);
		image->setMargin(50, Wt::Top);
	}));

	return anchor;
}


} /* namespace SiconfPage */
