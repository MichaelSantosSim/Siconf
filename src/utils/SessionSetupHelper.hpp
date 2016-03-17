/*
 * SessionSetupHelper.hpp
 *
 *  Created on: 20/04/2015
 *      Author: rafael
 */

#ifndef SRC_UTILS_SESSIONSETUPHELPER_HPP_
#define SRC_UTILS_SESSIONSETUPHELPER_HPP_

#include <Wt/Dbo/Session>
#include <Wt/Dbo/SqlConnection>
#include <Wt/Dbo/SqlConnectionPool>
#include <Wt/Dbo/FixedSqlConnectionPool>
#include <Wt/Dbo/backend/Sqlite3>

#include <unordered_map>

namespace SiconfUtils {
/**
 * Classe utilitaria que vai inicializar objetos Wt::Dbo::Session.
 */
class SessionSetupHelper {
public:
	enum class DataBase {
		SQLITE3
	};
	/**
	 * Vai fazer com que o functor edite a Session para se conectar com
	 * o banco de dados especificado.
	 * @param dataBase o banco ao qual sera feita a conexao.
	 */
	SessionSetupHelper(DataBase dataBase = DataBase::SQLITE3);

	/**
	 * Mapeia todas as tabelas na sessao.
	 * @param session a sessao do banco a ser configurada.
	 */
	void operator()(Wt::Dbo::Session& session) const;

private:
	DataBase _dataBase;
	static const std::string _dataBasePath;
	static Wt::Dbo::FixedSqlConnectionPool _connectionPoolSqlite3;
	static std::unordered_map<int, Wt::Dbo::SqlConnectionPool&> _connectionPoolMap;
};

} /* namespace PlatisAutomationUtils */

#endif /* SRC_UTILS_SESSIONSETUPHELPER_HPP_ */
