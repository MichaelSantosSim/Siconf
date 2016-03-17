/*
 * TestEnvironment.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#include "TestEnvironment.h"

namespace SiconfUtils {

TestEnvironment::TestEnvironment() : WContainerWidget() {
	_initialize();
	_setClickEvents();

	Wt::WTemplate* t = new Wt::WTemplate(Wt::WString::tr("testEnvironment"));
	t->bindWidget("button-group", toolbar);
	t->bindWidget("output-message", outPut);

	setStyleClass("blackBackground");

	addWidget(t);

}


Wt::WPushButton* TestEnvironment::createToolbarButton(std::string name){
	Wt::WPushButton* button = new Wt::WPushButton(name);
	button->setMargin(10, Wt::Bottom | Wt::Top | Wt::Left | Wt::Right);
	toolbar->addButton(button);
	return button;
}

void TestEnvironment::_initialize(){
	outPut = new Wt::WText();
	outPut->setMargin(10, Wt::Left);

	toolbar = new Wt::WToolBar();

	toolbar->setMargin(Wt::WLength::Auto, Wt::Left | Wt::Right);

	_disciplina = createToolbarButton("Disciplina");
	_usuario = createToolbarButton("Usuario");
	_professor = createToolbarButton("professor");

	addWidget(new Wt::WBreak());

	addWidget(outPut);
}

void TestEnvironment::_setClickEvents(){
	_disciplina->clicked().connect(this, &TestEnvironment::setDisciplinaDialog);
	_usuario->clicked().connect(this, &TestEnvironment::setUsuarioDialog);
	_professor->clicked().connect(this, &TestEnvironment::setProfessorDialog);
}

void TestEnvironment::setProfessorDialog(){


	auto ok = getOkButton();
	auto cancel = getCancelButton();

	auto dialog = getDialog("Cadastro de Professor");

	SiconfForms::ProfessorForm* professorForm = new SiconfForms::ProfessorForm();

	dialog->contents()->addWidget(professorForm);

	ok->clicked().connect(std::bind([=](){
		delete dialog;
	}));

	cancel->clicked().connect(std::bind([=](){
		delete dialog;
	}));

	dialog->footer()->addWidget(ok);
	dialog->footer()->addWidget(cancel);

	dialog->show();
}

void TestEnvironment::setDisciplinaDialog(){
	// TODO

	auto ok = getOkButton();
	auto cancel = getCancelButton();

	auto dialog = getDialog("Cadastro de Disciplina");


	SiconfForms::DisciplinaForm* disciplinaform = new SiconfForms::DisciplinaForm();

	dialog->contents()->addWidget(disciplinaform);

	ok->clicked().connect(std::bind([=](){
		if(disciplinaform->validate()){

			delete dialog;
		}
	}));

	cancel->clicked().connect(std::bind([=](){
		outPut->setText("Cadastro de disciplina cancelado");
		delete dialog;
	}));

	dialog->footer()->addWidget(ok);
	dialog->footer()->addWidget(cancel);


	dialog->show();
}

void TestEnvironment::setUsuarioDialog(){
	// TODO
	auto ok = getOkButton();
	auto cancel = getCancelButton();

	auto dialog = getDialog("Cadastro de Usuario");


	SiconfForms::UserForm* userform = new SiconfForms::UserForm();

	dialog->contents()->addWidget(userform);

	ok->clicked().connect(std::bind([=](){
		if(userform->validate()){
			outPut->setText(userform->usuario()->nome() + " cadastrado!");
			delete dialog;
		}
	}));

	cancel->clicked().connect(std::bind([=](){
		outPut->setText("Cadastro de usuario cancelado");
		delete dialog;
	}));

	dialog->footer()->addWidget(ok);
	dialog->footer()->addWidget(cancel);


	dialog->show();

}

Wt::WPushButton* TestEnvironment::getOkButton(){
	Wt::WPushButton* okButton = new Wt::WPushButton("Ok");
	okButton->setStyleClass("btn-primary");
	return okButton;
}

Wt::WPushButton* TestEnvironment::getCancelButton(){
	Wt::WPushButton* cancelButton = new Wt::WPushButton("Cancelar");
	cancelButton->setStyleClass("btn-warning");

	return cancelButton;
}

Wt::WDialog* TestEnvironment::getDialog(std::string title){
	Wt::WDialog* dialog = new Wt::WDialog();

	dialog->setWidth(Wt::WLength("50%"));
	dialog->setHeight(Wt::WLength("80%"));

	dialog->setTitleBarEnabled(true);
	dialog->titleBar()->setContentAlignment(Wt::AlignCenter);
	dialog->titleBar()->addWidget(new Wt::WText("<h3>" + title + "</h3>"));

	return dialog;
}

} /* namespace SiconfUtils */
