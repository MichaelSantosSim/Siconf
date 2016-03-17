/*
 * SessionSetupHelper.cpp
 *
 *  Created on: 20/04/2015
 *      Author: rafael
 */

#include "SessionSetupHelper.hpp"
#include <Wt/Dbo/FixedSqlConnectionPool>
#include <Wt/Dbo/Transaction>
#include "../model/models_defs.h"

namespace SiconfUtils {

const std::string SessionSetupHelper::_dataBasePath = "siconf.db";
//const std::string SessionSetupHelper::_dataBasePath = "/mnt/data/platis/platisAutomation.db";
Wt::Dbo::FixedSqlConnectionPool SessionSetupHelper::_connectionPoolSqlite3{new Wt::Dbo::backend::Sqlite3(_dataBasePath), 5};
std::unordered_map<int, Wt::Dbo::SqlConnectionPool&> SessionSetupHelper::_connectionPoolMap =
{
	{(int)DataBase::SQLITE3, _connectionPoolSqlite3}
};
SessionSetupHelper::SessionSetupHelper(DataBase dataBase) :
	_dataBase(dataBase) { }

void SessionSetupHelper::operator()(Wt::Dbo::Session& session) const {
	session.setConnectionPool(_connectionPoolMap.at((int)_dataBase));
	Wt::Dbo::Transaction trans(session);

	session.mapClass<SiconfModel::Endereco>		("endereco");
	session.mapClass<SiconfModel::Usuario>		("usuario");
	session.mapClass<SiconfModel::Aluno>		("aluno");
	session.mapClass<SiconfModel::Professor>	("professor");
	session.mapClass<SiconfModel::Disciplina>	("disciplina");
	session.mapClass<SiconfModel::Turma>		("turma");
	session.mapClass<SiconfModel::Nota>			("nota");
	session.mapClass<SiconfModel::Frequencia>	("frequencia");
	session.mapClass<SiconfModel::Avaliacao>	("avaliacao");
	session.mapClass<SiconfModel::Aula>			("aula");


}
} /* namespace PlatisAutomationUtils */
