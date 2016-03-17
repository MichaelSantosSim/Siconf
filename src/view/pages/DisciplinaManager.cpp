/*
 * DisciplinaManager.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: michael
 */

#include "DisciplinaManager.h"

namespace SiconfPage {

DisciplinaManager::DisciplinaManager(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina) :
										Wt::WContainerWidget(),
										_mainStack(new Wt::WStackedWidget(this)),
										_mainContainer(new Wt::WContainerWidget(_mainStack)),
										_dbSession(dbSession),
										_disciplina(disciplina)
										{
	Wt::Dbo::Transaction transaction(_dbSession);
	new Wt::WText("<h3> Listagem de Alunos - " + disciplina->nome() + " " + std::to_string(disciplina->turma()->serie()) + " serie " + disciplina->turma()->classe() + "</h3><br></br><br></br>", _mainContainer);
	_gerenciarAvaliacoes = new Wt::WPushButton("Avaliacoes", _mainContainer);
	_gerenciarAvaliacoes->setMargin(10, Wt::Right);
	_gerenciarAvaliacoes->setStyleClass("btn btn-primary");
	_gerenciarAvaliacoes->clicked().connect(this, &DisciplinaManager::showAdicionarAvaliacao);
	_alunoList =  new SiconfList::AlunoList(_dbSession, _disciplina);
	_alunoList->setMargin(50, Wt::Top);
	_alunoList->destroyed().connect(std::bind([=](){
		delete this;
	}));

	Wt::Dbo::ptr<SiconfModel::Aula> aula = _dbSession.find<SiconfModel::Aula>("where data = ? and aulas_disciplina_id = ?").bind(Wt::WDate::currentDate().toString("yyyy-MM-dd")).bind(_disciplina.id());

	_fazerChamada = new Wt::WPushButton("Fazer Chamada", _mainContainer);
	_fazerChamada->setStyleClass("btn btn-primary");
	fazerChamadaConnection = _fazerChamada->clicked().connect(this, &DisciplinaManager::showFazerChamada);

	if(aula){
		_fazerChamada->setText("Refazer Chamada");
		_fazerChamada->clicked().disconnect(fazerChamadaConnection);
		_fazerChamada->clicked().connect(this, &DisciplinaManager::showRefazerChamada);
	}
	_mainContainer->addWidget(_alunoList);


}
void DisciplinaManager::showRefazerChamada(){
	Wt::Dbo::Transaction transaction(_dbSession);
	try{
		Wt::Dbo::ptr<SiconfModel::Aula> aula = _dbSession.find<SiconfModel::Aula>("where data = ? and aulas_disciplina_id = ?").bind(Wt::WDate::currentDate().toString("yyyy-MM-dd")).bind(_disciplina.id());

		SiconfForms::ChamadaForm* chamada = new SiconfForms::ChamadaForm(_dbSession, _disciplina, aula);
		chamada->setWidth(Wt::WLength("40%"));
		_mainStack->addWidget(chamada);
		_mainStack->setCurrentWidget(chamada);
		chamada->destroyed().connect(std::bind([=](){
			_mainStack->setCurrentIndex(0);
			_alunoList->setTable();
		}));

	}catch(Wt::Dbo::Exception& e){
		new SiconfUtils::Popup("DisciplinaManager::showRefazerChamada()", e.what());
		return;
	}
}

void DisciplinaManager::showFazerChamada(){
	Wt::Dbo::Transaction transaction(_dbSession);
	try{
		SiconfForms::ChamadaForm* chamada = new SiconfForms::ChamadaForm(_dbSession, _disciplina);

		chamada->setWidth(Wt::WLength("40%"));
		_mainStack->addWidget(chamada);
		_mainStack->setCurrentWidget(chamada);
		chamada->destroyed().connect(std::bind([=](){
			Wt::Dbo::Transaction lambdatransaction(_dbSession);
			_mainStack->setCurrentIndex(0);
			_alunoList->setTable();
			Wt::Dbo::ptr<SiconfModel::Aula> aula = _dbSession.find<SiconfModel::Aula>("where data = ? and aulas_disciplina_id = ?").bind(Wt::WDate::currentDate().toString("yyyy-MM-dd")).bind(_disciplina.id());
			if(aula){
				_fazerChamada->setText("Refazer Chamada");
				_fazerChamada->clicked().disconnect(fazerChamadaConnection);
				_fazerChamada->clicked().connect(this, &DisciplinaManager::showRefazerChamada);
			}

		}));

	}catch(Wt::Dbo::Exception& e){
		new SiconfUtils::Popup("DisciplinaManager::showFazerChamada()", e.what());
		return;
	}

}


void DisciplinaManager::showAdicionarAvaliacao(){
	try{
		SiconfPages::AvaliacaoManager* avaliacao = new SiconfPages::AvaliacaoManager(_dbSession, _disciplina);
			avaliacao->setWidth(Wt::WLength("40%"));
			_mainStack->addWidget(avaliacao);
			_mainStack->setCurrentWidget(avaliacao);
			avaliacao->destroyed().connect(std::bind([=](){
				_mainStack->setCurrentIndex(0);
				_alunoList->setTable();

			}));
	}catch(Wt::Dbo::Exception& e){
		new SiconfUtils::Popup("DisciplinaManager::showAdicionarAvaliacao()", e.what());
		return;
	}

}

} /* namespace SiconfList */
