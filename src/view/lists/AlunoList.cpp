/*
 * AlunoList.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: michael
 */

#include "AlunoList.h"

namespace SiconfList {

AlunoList::AlunoList(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina):
	_dbSession(dbSession), _disciplina(disciplina){

	_table = new Wt::WTable(this);

	setTable();

	Wt::WPushButton* close = new Wt::WPushButton("Voltar", this);
	close->setStyleClass("btn btn-primary");
	close->clicked().connect(std::bind([this](){
		delete this;
	}));
}

void AlunoList::setTable(){

	Wt::Dbo::Transaction transaction(_dbSession);
	_table->clear();
	_table->setHeaderCount(1);
	_table->setStyleClass("table table-striped table-hover");
	_table->setWidth(500);

		Wt::Dbo::ptr<SiconfModel::Turma> turma = _disciplina->turma();

		Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Aluno>> alunos = turma->alunos();

		new Wt::WText("Nome", _table->elementAt(0,0));
		new Wt::WText("Frequencia", _table->elementAt(0,1));

		Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Avaliacao>> avaliacoes = _disciplina->avaliacoes();

		for(unsigned i = 1; i < (avaliacoes.size() + 1) ; i++){
			new Wt::WText("Av. " + std::to_string(i), _table->elementAt(0, _table->columnCount()));
		}

		new Wt::WText("Media", _table->elementAt(0, _table->columnCount()));

		for(auto aluno : alunos){
			int row = _table->rowCount();
			new Wt::WText(aluno->usuario()->nome(), _table->elementAt(row, 0));
			float presencas = 0.0;
			float total = 0.0;

			try{

				std::vector<Wt::Dbo::ptr<SiconfModel::Frequencia>> frequencias;

				total = _disciplina->aulas().size();

				Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Frequencia>> collFrequ = _dbSession.find<SiconfModel::Frequencia>("where frequencias_aluno_id = ?").bind(aluno.id());

				for(auto i : collFrequ){

					if(i->aula()->disciplina().id() == _disciplina.id()){
						if(i->presenca()){
							presencas +=1;
						}
					}
				}

				if(total > 0){
					for(auto i : frequencias){
						if(i->presenca()) presencas +=1;
					}
					presencas = ((presencas/total)* 100);
				}

			}catch(Wt::Dbo::Exception& e){
				std::cout << "AlunoList::setTable: " << e.what() << std::endl;
			}

			std::stringstream strPresencas;
			strPresencas << std::fixed << std::setprecision(1) << presencas;

			new Wt::WText(strPresencas.str() + " %", _table->elementAt(row, 1));
			unsigned col = 2;

			int qtdAvaliacoes = avaliacoes.size();
			float media = 0;

			for(auto avaliacao : avaliacoes){
				Wt::Dbo::ptr<SiconfModel::Nota> nota = _dbSession.find<SiconfModel::Nota>("where notas_avaliacao_id = ? and notas_aluno_id = ?").bind(avaliacao.id()).bind(aluno.id());
				if(nota){
					media+=nota->nota();
					std::stringstream strNotas;
					strNotas << std::fixed << std::setprecision(1) << nota->nota();
					Wt::WText* text = new Wt::WText(strNotas.str(), _table->elementAt(row, col));
					if(nota->nota() < 5){
						text->addStyleClass("text-red");
					}
				}
				col++;
			}


			if(qtdAvaliacoes == 0){
				media = 0;
			}else{
				media /= qtdAvaliacoes;
			}


			std::stringstream strMedia;
			strMedia << std::fixed << std::setprecision(1) << media;
			Wt::WText* text = new Wt::WText(strMedia.str(), _table->elementAt(row, _table->columnCount() -1));
			if(media < 5){
				text->addStyleClass("text-red");
			}
		}
}

//TODO fazer isso
float AlunoList::getFrequencia(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina, Wt::Dbo::ptr<SiconfModel::Aluno>  aluno){

	Wt::Dbo::Transaction transaction(_dbSession);

	Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Aula>> aulas = _dbSession.find<SiconfModel::Aula>().where("aulas_disciplina_id = ?").bind(disciplina.id());

	return 0.0;
}




} /* namespace SiconfList */
