/*
 * TurmaList.h
 *
 *  Created on: 06/09/2015
 *      Author: michael
 */

#ifndef SRC_VIEW_TURMALIST_H_
#define SRC_VIEW_TURMALIST_H_

#include <Wt/WContainerWidget>
#include <iostream>
#include <Wt/Dbo/Session>
#include <Wt/WText>
#include <Wt/WTable>
#include "../../model/models_defs.h"
#include "../../utils/Popup.h"

namespace SiconfList {

class TurmaList: public Wt::WContainerWidget {
public:
	TurmaList(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Professor> professor);

private:

	Wt::Dbo::Session& _dbSession;
	Wt::Dbo::ptr<SiconfModel::Professor> _professor;

};

} /* namespace SiconfList */

#endif /* SRC_VIEW_TURMALIST_H_ */
