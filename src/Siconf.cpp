
#include <iostream>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WBootstrapTheme>
#include <Wt/WTemplate>

#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Dbo>

#include "SiconfApplication.h"
#include "model/models_defs.h"
#include "utils/SessionSetupHelper.hpp"

using namespace std;
using namespace Wt;

WApplication *createApplication(const WEnvironment& env){
	Wt::WApplication* app = new Wt::WApplication(env);
	new Wt::WTemplate(Wt::WString::tr("css"), app->root());
	app->setTheme(new WBootstrapTheme());
	app->messageResourceBundle().use(app->appRoot() + "templates/forms");
	app->messageResourceBundle().use(app->appRoot() + "templates/pages");
	app->enableUpdates(true);
	app->setTitle("Sistema Integrado de Notas e Frequencia");
	app->root()->addWidget(new SiconfApplication());

    return app;
}

int main(int argc, char **argv){

	Wt::Dbo::Session session;
	SiconfUtils::SessionSetupHelper sessionSetup(SiconfUtils::SessionSetupHelper::DataBase::SQLITE3);
	try{
		sessionSetup(session);
		session.createTables();
		std::cout << "Tabelas criadas com sucesso!" << std::endl;
	}catch(Wt::Dbo::Exception& e){
		std::cout << "Erro no banco de dados:" << std::endl << e.what() << std::endl;
	}

	return WRun(7, argv, &createApplication);
}
