/*
 * AvaliacaoManager.cpp
 *
 *  Created on: Oct 25, 2015
 *      Author: michael
 */

#include "AvaliacaoManager.h"

namespace SiconfPages {


AvaliacaoManager::AvaliacaoManager(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina) :
																						Wt::WContainerWidget(),
																						_dbSession(dbSession),
																						_disciplina(disciplina),
																						_mainStack(new Wt::WStackedWidget(this)),
																						_mainPage(new Wt::WContainerWidget(_mainStack)),
																						_disciplinaTable(new Wt::WTable()){
	Wt::Dbo::Transaction transaction(_dbSession);
	new Wt::WText("<h3>Gerenciar Avaliacao</h3>");
	_adicionarAvaliacao = new Wt::WPushButton("Adicionar Avaliacao", _mainPage);
	_adicionarAvaliacao->setMargin(50, Wt::Bottom);
	_adicionarAvaliacao->clicked().connect(std::bind([=](){
		SiconfForms::AvaliacaoForm* formAvaliacao = new SiconfForms::AvaliacaoForm(_dbSession, _disciplina);
		_mainStack->addWidget(formAvaliacao);
		_mainStack->setCurrentWidget(formAvaliacao);
		formAvaliacao->destroyed().connect(this, &AvaliacaoManager::_backToMain);
	}));

	_setTable();

	_mainPage->addWidget(_disciplinaTable);

	Wt::WPushButton* voltar = new Wt::WPushButton("Voltar", _mainPage);
	voltar->setMargin(50, Wt::Top);
	voltar->addStyleClass("btn btn-primary");
	voltar->clicked().connect(std::bind([=](){
		delete this;
	}));
}

void AvaliacaoManager::_setTable(){

	Wt::Dbo::Transaction transaction(_dbSession);

	if(_disciplina->avaliacoes().size() >= 4){
		_adicionarAvaliacao->disable();
	}else if(_disciplina->avaliacoes().size() < 4){
		_adicionarAvaliacao->enable();
	}

	_disciplinaTable->clear();
	_disciplinaTable->setHeaderCount(1);
	_disciplinaTable->addStyleClass("table-striped table-hover");
	_disciplinaTable->setWidth(Wt::WLength("100%"));

	new Wt::WText("#", _disciplinaTable->elementAt(0, 0));
	new Wt::WText("Nome", _disciplinaTable->elementAt(0, 1));
	new Wt::WText("Excluir", _disciplinaTable->elementAt(0, 2));
	_disciplinaTable->rowAt(0)->setHeight(40);

	unsigned int numAvaliacao = 0;

	for(auto i : _disciplina->avaliacoes()){
		numAvaliacao++;
		unsigned int row = _disciplinaTable->rowCount();
		_disciplinaTable->rowAt(row)->setHeight(40);
		new Wt::WText(std::to_string(numAvaliacao), _disciplinaTable->elementAt(row, 0));
		SiconfWidget::Anchor<Wt::Dbo::ptr<SiconfModel::Avaliacao>>* disciplinaAnchor = new SiconfWidget::Anchor<Wt::Dbo::ptr<SiconfModel::Avaliacao>>(i, i->nome(), _disciplinaTable->elementAt(row, 1));

		disciplinaAnchor->clicked().connect(std::bind([=](){

		SiconfForms::AvaliacaoForm* formAvaliacao = new SiconfForms::AvaliacaoForm(_dbSession, _disciplina,  i);
			_mainStack->addWidget(formAvaliacao);
			_mainStack->setCurrentWidget(formAvaliacao);
			formAvaliacao->destroyed().connect(this, &AvaliacaoManager::_backToMain);
		}));

		Wt::WAnchor* deleteAnchor = new Wt::WAnchor(_disciplinaTable->elementAt(row, 2));
		deleteAnchor->setText("Apagar");
		deleteAnchor->addStyleClass("Wt-Anchor");
		deleteAnchor->clicked().connect(std::bind([=](){
			try{
				_apagarDisciplina(disciplinaAnchor->get());
				_setTable();
			}catch(std::exception& e){
				new SiconfUtils::Popup(e.what(), "Atencao");
			}
		}));

	}


}

void AvaliacaoManager::_apagarDisciplina(Wt::Dbo::ptr<SiconfModel::Avaliacao> avaliacao){
	Wt::Dbo::Transaction transaction(_dbSession);
	for(auto i : avaliacao->notas()){
		i.remove();
	}
	avaliacao.remove();
	_setTable();
}

void AvaliacaoManager::_backToMain(){
	_mainStack->setCurrentWidget(_mainPage);
	_setTable();
}

} /* namespace SiconfPages */
