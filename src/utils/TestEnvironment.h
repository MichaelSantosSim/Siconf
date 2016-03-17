/*
 * TestEnvironment.h
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#ifndef UTILS_TESTENVIRONMENT_H_
#define UTILS_TESTENVIRONMENT_H_

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WDialog>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WToolBar>
#include <Wt/WBreak>
#include <Wt/WLineEdit>

#include "../view/forms/DisciplinaForm.h"
#include "../view/forms/EnderecoForm.h"
#include "../view/forms/UserForm.h"
#include "../view/forms/ProfessorForm.h"

namespace SiconfUtils {

class TestEnvironment: public Wt::WContainerWidget {
public:
	TestEnvironment();

private:

	void setDisciplinaDialog();
	void setUsuarioDialog();
	void setProfessorDialog();

	Wt::WPushButton* createToolbarButton(std::string name);

	Wt::WPushButton* getOkButton();
	Wt::WPushButton* getCancelButton();

	Wt::WDialog* getDialog(std::string title);

	void _initialize();
	void _setClickEvents();

	Wt::WToolBar* toolbar;
	Wt::WPushButton* _disciplina;
	Wt::WPushButton* _usuario;
	Wt::WPushButton* _professor;

	Wt::WText* outPut;

};

} /* namespace SiconfUtils */

#endif /* UTILS_TESTENVIRONMENT_H_ */
