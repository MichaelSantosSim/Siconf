/*
 * LoginPage.h
 *
 *  Created on: Aug 23, 2015
 *      Author: michael
 */

#ifndef VIEW_PAGES_LOGINPAGE_H_
#define VIEW_PAGES_LOGINPAGE_H_

#include "AbstractPage.h"
#include "../../utils/Login.h"
#include "../../model/models_defs.h"
#include "HomeProfessor.h"
#include "HomeAluno.h"
#include "../../utils/Popup.h"
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/Dbo/Transaction>
#include <Wt/WText>
#include <Wt/WTemplate>
#include <Wt/WMessageBox>
#include <Wt/WApplication>

namespace SiconfPage {

class LoginPage: public AbstractPage {
public:
	LoginPage(SiconfUtils::PageNavigator* navigator, Wt::Dbo::Session& dbSession);


private:
	SiconfUtils::PageNavigator* _navigator;
	Wt::WLineEdit* _userName;
	Wt::WLineEdit* _password;
	Wt::WPushButton* _enter;
	Wt::WText* _out;
	SiconfUtils::Login* _login;
	void _initialize();
	void _setPage(Wt::Dbo::ptr<SiconfModel::Usuario> usuario);

	Wt::Signal<SiconfModel::Usuario, bool> _loginChanged;
	Wt::Dbo::Session& _dbSession;
};

} /* namespace SiconfPage */

#endif /* VIEW_PAGES_LOGINPAGE_H_ */
