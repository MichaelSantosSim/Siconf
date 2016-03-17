/*
 * AvaliacaoForm.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: michael
 */

#include "AvaliacaoForm.h"

namespace SiconfForms {

AvaliacaoForm::AvaliacaoForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina) :
														Wt::WContainerWidget(), _list(new Wt::WTable()), _dbSession(dbSession), _disciplina(disciplina){
	_initialize();
}

AvaliacaoForm::AvaliacaoForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina, Wt::Dbo::ptr<SiconfModel::Avaliacao> avaliacao) :
														Wt::WContainerWidget(), _list(new Wt::WTable()), _dbSession(dbSession), _disciplina(disciplina), _avaliacao(avaliacao){
	_initialize();
	_fillForm();
}

void AvaliacaoForm::_fillForm(){
	Wt::Dbo::Transaction transaction(_dbSession);

	_nome->setText(_avaliacao->nome());
	_nome->setDisabled(true);
	for(auto i : _avaliacao->notas()){
		for(auto j : _sortList){
			if(j.second.id() == i->aluno().id()){
				std::cout << i->aluno()->usuario()->nome() << ": " << i->nota() << std::setprecision(1) << std::endl;
				j.first->setValue(i->nota());
			}
		}
	}
}

void AvaliacaoForm::_initialize(){

	_nome = new Wt::WLineEdit();
	_nome->setAttributeValue("placeholder", "Nome da Avaliacao");
	_nome->setWidth(Wt::WLength("50%"));
	_nome->addStyleClass("form-control");
	_nome->setInline(true);
	addWidget(_nome);

	_list->setWidth(Wt::WLength("100%"));
	_list->addStyleClass("table-striped table-hover");

	_list->setMargin(50, Wt::Top);

	Wt::Dbo::Transaction transaction(_dbSession	);

	for(auto i : _disciplina->turma()->alunos()){
		auto usuario = i->usuario();
		Wt::WDoubleSpinBox* spinBox = new Wt::WDoubleSpinBox();
		spinBox->setDecimals(1);
		spinBox->setMinimum(0.0);
		spinBox->setMaximum(10.0);
		spinBox->setStyleClass("form-control");
		Wt::WDoubleValidator* validator = new Wt::WDoubleValidator();
		validator->setMandatory(true);
		spinBox->setValidator(validator);

		_sortList.push_back(std::make_pair(spinBox, i));
	}

	auto sortAlg = [](std::pair<Wt::WDoubleSpinBox*, Wt::Dbo::ptr<SiconfModel::Aluno>> par1, std::pair<Wt::WDoubleSpinBox*, Wt::Dbo::ptr<SiconfModel::Aluno>>par2){
		return par1.second->usuario()->nome() < par2.second->usuario()->nome();
	};

	std::sort(std::begin(_sortList), std::end(_sortList), sortAlg);

	for(auto i : _sortList){
		int row = _list->rowCount();
		Wt::WText* name = new Wt::WText(i.second->usuario()->nome() + " " + i.second->usuario()->sobrenome(), _list->elementAt(row, 0));
		_list->elementAt(row, 1)->addWidget(i.first);
		name->setMargin(10, Wt::Right);
		_list->elementAt(row, 1)->setHeight(40);
		_list->elementAt(row, 1)->setWidth(100);

	}

	addWidget(_list);

	Wt::WPushButton* save = new Wt::WPushButton("Salvar", this);
	save->setStyleClass("btn btn-success");
	save->setMargin(10, Wt::Right);
	save->clicked().connect(std::bind([=](){
		_save();
	}));

	Wt::WPushButton* cancel = new Wt::WPushButton("Cancelar", this);
	cancel->setStyleClass("btn btn-primary");
	cancel->clicked().connect(std::bind([=](){
		delete this;
	}));


}

void AvaliacaoForm::_save(){
	Wt::Dbo::Transaction transaction(_dbSession);

	if(_nome->text().toUTF8().size() == 0){
		new SiconfUtils::Popup("Digite um nome", "Atencao");
		return;
	}

	for(auto i : _sortList){
		if(i.first->value() < 0 || i.first->value() > 10){
			new SiconfUtils::Popup("Notas acima de 10 ou abaixo de 0 nao sao permitidas! Verifique os campos em vermelho.", "Atencao");
			return;
		}
	}

	if(_avaliacao){
		for(auto i : _avaliacao->notas()){
			for(auto j : _sortList){
				if(j.second.id() == i->aluno().id()){
					i.modify()->definirNota(j.first->value());
				}
			}
		}
	}else{

		if(_nome->text().toUTF8().size() == 0){
			new SiconfUtils::Popup("Atencao", "Digite um nome");
			return;
		}

		Wt::Dbo::ptr<SiconfModel::Avaliacao> avaliacao = _dbSession.add(new SiconfModel::Avaliacao(_nome->text().toUTF8(), _disciplina, 1.0));

		for(auto i : _sortList){
			SiconfModel::Nota* nota = new SiconfModel::Nota(avaliacao, i.second, i.first->value());
			_dbSession.add(nota);
		}
	}

	delete this;
}

} /* namespace SiconfForms */
