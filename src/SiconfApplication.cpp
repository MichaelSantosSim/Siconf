/*
 * SiconfApplication.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: michael
 */

#include "SiconfApplication.h"


SiconfApplication::SiconfApplication(){


	_setupSession();
	_initialize();


	_navigator->addPage(_login);
	_navigator->setInternalPath(Wt::WApplication::instance()->internalPath());

	//	addWidget(new SiconfUtils::TestEnvironment());
}

void SiconfApplication::_initialize(){
	_navigator = new SiconfUtils::PageNavigator(this);
	_login =  new SiconfPage::LoginPage(_navigator, _dbSession);
}

void SiconfApplication::_setupSession(){
	SiconfUtils::SessionSetupHelper sessionSetup(SiconfUtils::SessionSetupHelper::DataBase::SQLITE3);

	try{
		sessionSetup(_dbSession);
		}catch(Wt::Dbo::Exception& e){
			std::cout << "[SiconfApplication::_setupSession()]Erro........... " << e.what() << std::endl;
	}

}
