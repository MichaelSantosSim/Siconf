/*
 * AlunoList.h
 *
 *  Created on: Sep 17, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_LISTS_ALUNOLIST_H_
#define SRC_VIEW_LISTS_ALUNOLIST_H_

#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/Dbo>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include "../../model/models_defs.h"

namespace SiconfList {

class AlunoList: public Wt::WContainerWidget {
public:
	AlunoList(Wt::Dbo::Session& dbSession, Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina);
	void setTable();
private:
	Wt::Dbo::Session& _dbSession;
	Wt::WTable* _table;
	Wt::Dbo::ptr<SiconfModel::Disciplina> _disciplina;
	float getFrequencia(Wt::Dbo::ptr<SiconfModel::Disciplina> disciplina, Wt::Dbo::ptr<SiconfModel::Aluno> aluno);
};

} /* namespace SiconfList */

#endif /* SRC_VIEW_LISTS_ALUNOLIST_H_ */
