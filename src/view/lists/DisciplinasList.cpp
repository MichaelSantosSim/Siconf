/*
 * DisciplinasList.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: michael
 */

#include "DisciplinasList.h"

namespace SiconfList {

typedef Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Turma>> Turmas;
typedef Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Disciplina>> Disciplinas;
typedef SiconfModel::Turma::Turno smtt;

DisciplinasList::DisciplinasList(Wt::Dbo::ptr<SiconfModel::Professor> professor, Wt::Dbo::Session& session)
: Wt::WContainerWidget(),
  _mainStack(new Wt::WStackedWidget(this)),
  _dbSession(session), _list(new Wt::WTable(_mainStack)),
  _turnos{{smtt::Manha, "Manha"},
		  {smtt::Tarde, "Tarde"},
		  {smtt::Noite, "Noite"}}{


			  Wt::WContainerWidget* disciplinaList = new Wt::WContainerWidget(_mainStack);

			  disciplinaList->setContentAlignment(Wt::AlignCenter);
			  	_list->setStyleClass("table table-striped table-responsive table-hover");
			  	_setHeader();

			  	Wt::Dbo::Transaction transaction(_dbSession);

			  	Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Disciplina>> disciplinas = professor->disciplinas();

			  	for(auto disciplina : disciplinas){

			  		int row = _list->rowCount();
			  		SiconfWidget::Anchor<Wt::Dbo::ptr<SiconfModel::Disciplina>>* anchor = new SiconfWidget::Anchor<Wt::Dbo::ptr<SiconfModel::Disciplina>>(disciplina, _list->elementAt(row, 0));

			  		anchor->setText(disciplina->nome());

			  		anchor->clicked().connect(std::bind([=](){

			  			try{
			  				std::string nomeTurma = anchor->get()->turma()->nome();
			  				std::string nomeDisciplina =  anchor->get()->nome();

			  				SiconfPage::DisciplinaManager* disciplinaManager=  new SiconfPage::DisciplinaManager(_dbSession, anchor->get());
			  				_mainStack->addWidget(disciplinaManager);
			  				_mainStack->setCurrentWidget(disciplinaManager);
			  				disciplinaManager->destroyed().connect(std::bind([=](){
			  					_mainStack->setCurrentIndex(0);
			  				}));


			  			}catch(std::exception& e){
			  				std::cout << "[TurmaList::TurmaList() anchor->clicked] Erro........... " << e.what() << std::endl;
			  				SiconfUtils::Popup* popup = new SiconfUtils::Popup(e.what(), "Error");
			  			}
			  		}));

			  		new Wt::WText(disciplina->turma()->nome(), _list->elementAt(row, 1));
			  		new Wt::WText(_turnos.at(disciplina->turma()->turno()), _list->elementAt(row, 2));
			  	}

}

void DisciplinasList::_setHeader(){
	_list->setHeaderCount(1);
	new Wt::WText("Disciplina", _list->elementAt(0, 0));
	new Wt::WText("Turma", _list->elementAt(0, 1));
	new Wt::WText("Turno", _list->elementAt(0, 2));
}

} /* namespace SiconfList */
