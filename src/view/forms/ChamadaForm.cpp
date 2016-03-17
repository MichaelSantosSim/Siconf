/*
 * ChamadaForm.cpp
 *
 *  Created on: Oct 22, 2015
 *      Author: michael
 */

#include "ChamadaForm.h"

namespace SiconfForms {

ChamadaForm::ChamadaForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina) :
														_dbSession(dbSession),
														_disciplina(disciplina){
	_initialize();
}

ChamadaForm::ChamadaForm(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina, Wt::Dbo::ptr<SiconfModel::Aula> aula) :
																_dbSession(dbSession),
																_disciplina(disciplina),
																_aula(aula){
	try{
		_initialize();
		Wt::Dbo::Transaction transaction(_dbSession	);
		for(auto i : sortList){
			Wt::Dbo::ptr<SiconfModel::Frequencia> frequencia = _dbSession.find<SiconfModel::Frequencia>("where frequencias_aula_id = ? and frequencias_aluno_id = ?").bind(_aula.id()).bind(i.second.id());
			if(frequencia){
				i.first->setChecked(frequencia->presenca());
			}else{
				std::cout << "ChamadaForm::ChamadaForm() ................ Frequencia nao encontrada!" << std::endl;
			}
		}
	}catch(std::exception& e){
		new SiconfUtils::Popup("ChamadaForm::ChamadaForm()", e.what());
	}
}


void ChamadaForm::_initialize(){
	Wt::Dbo::Transaction transaction(_dbSession);

	Wt::WText* title = new Wt::WText("<h3>Diario de Classe: " + Wt::WDate::currentDate().toString("dd/MM/yyyy").toUTF8() + "</h3> <br></br><br></br>");

		addWidget(title);
		Wt::WPushButton* fazerChamada = new Wt::WPushButton("Percorrer turma", this);

		fazerChamada->setStyleClass("btn btn-primary");

		fazerChamada->clicked().connect(std::bind([=](){
			new AutoChamada(_dbSession, sortList);
		}));

		fazerChamada->setMargin(20, Wt::Bottom);
		_list =  new Wt::WTable(this);


		Wt::WPushButton* save = new Wt::WPushButton("Salvar", this);
		save->setStyleClass("btn btn-success");
		save->setMargin(10, Wt::Right);
		save->clicked().connect(std::bind([=](){
			_save();
			delete this;
		}));

		Wt::WPushButton* cancel = new Wt::WPushButton("Cancelar", this);
		cancel->setStyleClass("btn btn-primary");
		cancel->clicked().connect(std::bind([=](){
			delete this;
		}));

	_list->setWidth(Wt::WLength("100%"));
	_list->addStyleClass("table-striped table-hover");
	_list->setMargin(50, Wt::Bottom);
	new Wt::WText("Aluno", _list->elementAt(0,0));
	new Wt::WText("Presente", _list->elementAt(0,1));
	_list->setHeaderCount(1);


	for(auto i : _disciplina->turma()->alunos()){
		Wt::WCheckBox* checkbox = new Wt::WCheckBox();
		sortList.push_back(std::make_pair(checkbox, i));
	}

	auto sortAlg = [](std::pair<Wt::WCheckBox*, Wt::Dbo::ptr<SiconfModel::Aluno>> par1, std::pair<Wt::WCheckBox*, Wt::Dbo::ptr<SiconfModel::Aluno>>par2){
		return par1.second->usuario()->nome() < par2.second->usuario()->nome();
	};

	std::sort(std::begin(sortList), std::end(sortList), sortAlg);

	for(auto i : sortList){
		int row = _list->rowCount();
		Wt::WText* name = new Wt::WText(i.second->usuario()->nome() + " " + i.second->usuario()->sobrenome(), _list->elementAt(row, 0));
		name->setMargin(10, Wt::Right);
		_list->elementAt(row, 1)->addWidget(i.first);
		_list->elementAt(row, 1)->setHeight(40);
		_list->elementAt(row, 1)->setWidth(100);

	}
}


void ChamadaForm::_save(){
	Wt::Dbo::Transaction transaction(_dbSession);

	if(_aula){
		std::cout << "Aula set: updating..." << std::endl;
		for(auto i : sortList){
			Wt::Dbo::ptr<SiconfModel::Frequencia> frequencia = _dbSession.find<SiconfModel::Frequencia>("where frequencias_aula_id = ? and frequencias_aluno_id = ?").bind(_aula.id()).bind(i.second.id());
			if(frequencia){
				frequencia.modify()->definirPresenca(i.first->isChecked());
			}else{
				std::cout << "ChamadaForm::Save() ........... Frequencia not found" << std::endl;
			}
		}

	}else{
		std::cout << "Aula not set: creating..." << std::endl;
		_aula = _dbSession.add(new SiconfModel::Aula(_disciplina));
		for(auto i : sortList){
			_dbSession.add(new SiconfModel::Frequencia(_aula, i.second, i.first->isChecked()));
		}
	}

	transaction.commit();
}



// class AutoChamada

AutoChamada::AutoChamada(Wt::Dbo::Session& dbSession, std::vector<std::pair<Wt::WCheckBox*, Wt::Dbo::ptr<SiconfModel::Aluno>>> list) :
																								Wt::WDialog(),
																								_dbSession(dbSession),
																								_list(list),
																								index(0){

	Wt::Dbo::Transaction transaction(_dbSession);

	_presente = new Wt::WPushButton("Presente", footer());
	_ausente = new Wt::WPushButton("Ausente", footer());
	_anterior = new Wt::WPushButton("Anterior", footer());
	_cancelar = new Wt::WPushButton("Cancelar", footer());

	new Wt::WText("<h3>Chamada Automatica</h3>", titleBar());
	titleBar()->setContentAlignment(Wt::AlignCenter);
	contents()->setContentAlignment(Wt::AlignCenter);
	footer()->setContentAlignment(Wt::AlignCenter);

	_presente->clicked().connect(this, &AutoChamada::_presenteClicked);
	_ausente->clicked().connect(this, &AutoChamada::_ausenteClicked);
	_anterior->clicked().connect(this, &AutoChamada::_anteriorClicked);
	_cancelar->clicked().connect(this, &AutoChamada::_cancelClicked);

	_presente->setStyleClass("btn-success");
	_ausente->setStyleClass("btn-warning");
	_anterior->setStyleClass("btn-primary");
	_cancelar->setStyleClass("btn-danger");

	rejectWhenEscapePressed();

	auto aluno = _list.begin()->second->usuario();
	_name = new Wt::WText("<h4>" + aluno->nome() + " " + aluno->sobrenome() + "</h4>", contents());
	setWidth(Wt::WLength("30%"));
	show();
}

void AutoChamada::_presenteClicked(){

	Wt::Dbo::Transaction transaction(_dbSession);

	_list.at(index).first->setChecked();
	index++;
	if(index >= _list.size()){
		accept();
		return;
	}
	auto aluno = _list.at(index).second->usuario();
	_name->setText("<h4>" + aluno->nome() + " " + aluno->sobrenome() + "</h4>");
}

void AutoChamada::_ausenteClicked(){
	Wt::Dbo::Transaction transaction(_dbSession);

	_list.at(index).first->setUnChecked();
	index++;
	if(index >= _list.size()){
		accept();
		return;
	}
	auto aluno = _list.at(index).second->usuario();
	_name->setText("<h4>" + aluno->nome() + " " + aluno->sobrenome() + "</h4>");

}

void AutoChamada::_anteriorClicked(){
	Wt::Dbo::Transaction transaction(_dbSession);

	if(index > 0){
		index--;
		auto aluno = _list.at(index).second->usuario();
		_name->setText("<h4>" + aluno->nome() + " " + aluno->sobrenome() + "</h4>");
	}
}

void AutoChamada::_cancelClicked(){
	reject();
}

} /* namespace SiconfForms */
