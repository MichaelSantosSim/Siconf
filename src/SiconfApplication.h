/*
 * SiconfApplication.h
 *
 *  Created on: Jun 11, 2015
 *      Author: michael
 */

#ifndef SICONFAPPLICATION_H_
#define SICONFAPPLICATION_H_


#include <Wt/WContainerWidget>
#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>
#include <Wt/WMessageBox>
#include <Wt/Dbo/Session>

#include "view/forms/UserForm.h"
#include "utils/SessionSetupHelper.hpp"
#include "view/forms/DisciplinaForm.h"
#include "utils/PageNavigator.h"
#include "model/models_defs.h"


//Paginas
#include "utils/TestEnvironment.h"
#include "view/pages/LoginPage.h"
#include "view/pages/HomeProfessor.h"

class SiconfApplication: public Wt::WContainerWidget {
public:
	SiconfApplication();


private:

	void _setupSession();
	void _initialize();
	SiconfUtils::PageNavigator* _navigator;
	SiconfPage::LoginPage* _login;
	Wt::Dbo::Session _dbSession;

};

#endif /* SICONFAPPLICATION_H_ */
