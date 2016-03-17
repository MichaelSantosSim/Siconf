/*
 * Login.h
 *
 *  Created on: Sep 1, 2015
 *      Author: michael
 */

#ifndef UTILS_LOGIN_H_
#define UTILS_LOGIN_H_
#include "../model/models_defs.h"
#include "PageNavigator.h"
#include <Wt/WApplication>
#include <Wt/Dbo/Session>
#include <map>

namespace SiconfUtils {

class Login {

public:


	Login(Wt::Dbo::Session& dbSession);
	Wt::Dbo::ptr<SiconfModel::Usuario> verifyLogin(std::string login);
	bool verifyPassword(Wt::Dbo::ptr<SiconfModel::Usuario> usuario, std::string password);
	Wt::Dbo::ptr<SiconfModel::Usuario> usuario(std::string login);

	Wt::Dbo::ptr<SiconfModel::Professor> getProfessor(Wt::Dbo::ptr<SiconfModel::Usuario> usuario);
	Wt::Dbo::ptr<SiconfModel::Aluno> getAluno(Wt::Dbo::ptr<SiconfModel::Usuario> usuario);

private:

	std::map<std::string, SiconfModel::Usuario::TipoUsuario> _userMap;
	Wt::Dbo::Session& _dbSession;
};

} /* namespace SiconfUtils */

#endif /* UTILS_LOGIN_H_ */
