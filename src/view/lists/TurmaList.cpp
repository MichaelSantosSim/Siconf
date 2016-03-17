/*
 * TurmaList.cpp
 *
 *  Created on: 06/09/2015
 *      Author: michael
 */

#include "TurmaList.h"
#include "../widgets/Anchor.h"

namespace SiconfList {



TurmaList::TurmaList(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Professor> professor) : Wt::WContainerWidget(),
																									_dbSession(dbSession),
																									_professor(professor){
	Wt::Dbo::Transaction transaction(_dbSession);
//	Wt::WTable* table = new Wt::WTable(this);

	new Wt::WText("Ola, eu sou o TurmaList!", this);
}



} /* namespace SiconfList */
