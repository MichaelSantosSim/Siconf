/*
 * Login.cpp
 *
 *  Created on: Sep 1, 2015
 *      Author: michael
 */

#include "Login.h"

namespace SiconfUtils {

typedef SiconfModel::Usuario SMU;

Login::Login(Wt::Dbo::Session& dbSession) :
			_userMap	{{"RA", SMU::_Aluno},
						{"RP", SMU::_Professor},
						{"ra", SMU::_Aluno},
						{"rp", SMU::_Professor},
						{"AD", SMU::_Administrador},
						{"ad", SMU::_Administrador}}, _dbSession(dbSession){


}

Wt::Dbo::ptr<SiconfModel::Usuario> Login::verifyLogin(std::string login){

	Wt::Dbo::Transaction transaction(_dbSession);
	Wt::Dbo::ptr<SMU> usuario =_dbSession.find<SiconfModel::Usuario>().where("login = ?").bind(login);
	return usuario;

}


Wt::Dbo::ptr<SiconfModel::Professor> Login::getProfessor(Wt::Dbo::ptr<SiconfModel::Usuario> usuario){
	Wt::Dbo::Transaction transaction(_dbSession);
	Wt::Dbo::ptr<SiconfModel::Professor> professor =_dbSession.find<SiconfModel::Professor>().where("usuario_id = ?").bind(usuario.id());
	return professor;
}

Wt::Dbo::ptr<SiconfModel::Aluno> Login::getAluno(Wt::Dbo::ptr<SiconfModel::Usuario> usuario){

	Wt::Dbo::Transaction transaction(_dbSession);
	Wt::Dbo::ptr<SiconfModel::Aluno> aluno =_dbSession.find<SiconfModel::Aluno>().where("usuario_id = ?").bind(usuario.id());
	return aluno;
}


bool Login::verifyPassword(Wt::Dbo::ptr<SiconfModel::Usuario> usuario, std::string senha){
	Wt::Dbo::Transaction transaction(_dbSession);
	return senha == usuario->senha();
}

Wt::Dbo::ptr<SiconfModel::Usuario> Login::usuario(std::string login){

	Wt::Dbo::Transaction transaction(_dbSession);

	Wt::Dbo::ptr<SMU> usuario =_dbSession.find<SiconfModel::Usuario>().where("login = ?").bind(login.substr(2, login.size()));

	return usuario;
}

} /* namespace SiconfUtils */
