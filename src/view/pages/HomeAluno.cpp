/*
 * HomeAluno.cpp
 *
 *  Created on: Oct 25, 2015
 *      Author: michael
 */

#include "HomeAluno.h"

namespace SiconfPage {

HomeAluno::HomeAluno(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Aluno> aluno) :
																				AbstractPage("/home_aluno/"),
																				_dbSession(dbSession),
																				_mainTable(new Wt::WTable()),
																				_aluno(aluno),
																				_content(new Wt::WContainerWidget()){
	Wt::Dbo::Transaction transaction(_dbSession);
	Wt::WTemplate* t = new Wt::WTemplate(Wt::WString::tr("home_aluno"), this);
	_content->setWidth(Wt::WLength("100%"));
	t->bindWidget("home_aluno_content", _content);
	new Wt::WText("<h2>"+ aluno->usuario()->nome() + " " + aluno->usuario()->sobrenome() + " - " + aluno->turma()->nome() + "</h2>", _content);
	_setTable(_mainTable);
	_content->addWidget(_mainTable);

	Wt::WPushButton* button = new Wt::WPushButton("Imprimir");
	t->bindWidget("print_button", button);
	t->bindWidget("about", _getShowAbout());

	button->setStyleClass("btn btn-primary");
	button->clicked().connect(std::bind([=](){
		doJavaScript("window.print();");
	}));





//	try{
//		Wt::WContainerWidget *container = new Wt::WContainerWidget();
//			Wt::WResource *pdf = new SiconfUtils::SamplePdfResource(container);
//			Wt::WPushButton* download = new Wt::WPushButton("Imprimir", this);
//			download->setLink(pdf);
//	}catch(std::exception& e){
//		new SiconfUtils::Popup(e.what(), "Erro");
//	}
}

void HomeAluno::_setTable(Wt::WTable* table){
	table->clear();
	table->setMargin(50, Wt::Top);
	table->addStyleClass("table table-striped table-hover form-inline");
	table->setHeaderCount(1);
	table->setWidth(Wt::WLength("100%"));

	new Wt::WText("Materia", table->elementAt(0, 0));
	new Wt::WText("Av. 1", table->elementAt(0, 1));
	new Wt::WText("Av. 2", table->elementAt(0, 2));
	new Wt::WText("Av. 3", table->elementAt(0, 3));
	new Wt::WText("Av. 4", table->elementAt(0, 4));
	new Wt::WText("Media", table->elementAt(0, 5));
	new Wt::WText("Frequencia", table->elementAt(0, 6));


	for(auto disciplina : _aluno->turma()->disciplinas()){
		int row = table->rowCount();

		int notaCol = 1;
		for(auto nota : _aluno->notas()){
			if(nota->avaliacao()->disciplina().id() == disciplina.id()){
				std::stringstream strNota;
				strNota << std::fixed << std::setprecision(1) << nota->nota();
				Wt::WText* text = new Wt::WText(strNota.str(), table->elementAt(row, notaCol));
				if(nota->nota() < 5 ){
					text->addStyleClass("text-red");
				}
				notaCol++;
			}
		}

		while(notaCol < 5){
			new Wt::WText("--", table->elementAt(row, notaCol));
			notaCol++;
		}

		float media = _getMedia(disciplina);

		std::stringstream strMedia;
		strMedia << std::fixed << std::setprecision(1) << media;


		new Wt::WText(disciplina->nome(), table->elementAt(row, 0));
		Wt::WText* mediaText = new Wt::WText(strMedia.str(), table->elementAt(row, 5));
		if(media < 5 ){
			mediaText->addStyleClass("text-red");
		}

		std::stringstream strFrequencia;
		strFrequencia << std::fixed << std::setprecision(1) << _getFrequecia(disciplina);

		new Wt::WText(strFrequencia.str() + '%', table->elementAt(row, 6));
		table->rowAt(row)->setHeight(40);
	}
}

float HomeAluno::_getMedia(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina){

	Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Avaliacao>> avaliacoes =  disciplina->avaliacoes();
	int qtdAvaliacoes = avaliacoes.size();
	float media = 0;

	if(avaliacoes.size() == 0){
		return 0;
	}

	for(auto avaliacao : avaliacoes){
		Wt::Dbo::ptr<SiconfModel::Nota> nota = _dbSession.find<SiconfModel::Nota>("where notas_avaliacao_id = ? and notas_aluno_id = ?").bind(avaliacao.id()).bind(_aluno.id());
		if(nota){
			media+=nota->nota();
			std::stringstream strNotas;
			strNotas << std::fixed << std::setprecision(1) << nota->nota();
		}
	}

	media /= qtdAvaliacoes;

	return media;
}

float HomeAluno::_getFrequecia(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina){

	int presencas = 0;
	float total = disciplina->aulas().size();

	if(total == 0){
		return 0;
	}

	std::vector<Wt::Dbo::ptr<SiconfModel::Frequencia>> frequencias;

	Wt::Dbo::collection<Wt::Dbo::ptr<SiconfModel::Frequencia>> collFrequ = _dbSession.find<SiconfModel::Frequencia>("where frequencias_aluno_id = ?").bind(_aluno.id());

	for(auto i : collFrequ){

		if(i->aula()->disciplina().id() == disciplina.id()){
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

	return presencas;
}

Wt::WAnchor* HomeAluno::_getShowAbout(){
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

} /* namespace SiconfPages */
