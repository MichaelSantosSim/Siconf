/*
 * FieldSet.h
 *
 *  Created on: Jul 5, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_FORM_H_
#define VIEW_FORMS_FORM_H_

#include <Wt/WTemplate>
#include <Wt/WContainerWidget>
#include <Wt/WValidator>
#include "../fields/AbstractField.h"
#include <vector>
#include "../fields/LineField.h"

namespace SiconfForms {

class Form: public Wt::WTemplate {
public:
	Form(std::string titulo = "Formulario", Wt::WContainerWidget* parent = 0);
	void addField(SiconfFields::AbstractField* field);
	bool validate();
	void reset();

	std::vector<SiconfFields::AbstractField*> group() const {return _fields;};
	void setTitle(std::string title);
private:

	Wt::WText* _titulo;

	Wt::WContainerWidget* _container;
	std::vector<SiconfFields::AbstractField*> _fields;

};

} /* namespace SiconfForms */

#endif /* VIEW_FORMS_FORM_H_ */
