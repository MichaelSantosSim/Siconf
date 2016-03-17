/*
 * ListField.h
 *
 *  Created on: Aug 2, 2015
 *      Author: michael
 */

#ifndef VIEW_FIELDS_LISTFIELD_H_
#define VIEW_FIELDS_LISTFIELD_H_

#include "AbstractField.h"
#include <Wt/WComboBox>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WBreak>

namespace SiconfFields {
template <class T>
class ListField: public AbstractField {
public:
	ListField();
	bool validate(){return true;};
	void setHeader(std::string header);
	void reset(){};
	void addItem(std::string itemName, T item);
	Wt::WComboBox* comboBox(){return _itensCombo;}
	std::vector<T> getList();
private:
	// todo reimplementar a combobox com template
	void _setTemplate();
	void _updateInvalidMessage(std::string message);
	void _updateLabel(std::string label);
	void _setStyle();


	Wt::WComboBox* _itensCombo;
	Wt::WPushButton* _addItem;
	Wt::WTable* _list;
	std::map<int, T> _listMap;

	Wt::WText* _label;
	Wt::WText* _invalidMessage;
	Wt::WText* _listHeader;
};


template <class T>
ListField<T>::ListField() :
	AbstractField(),
	_itensCombo(new Wt::WComboBox()),
	_addItem(new Wt::WPushButton("Add")),
	_list(new Wt::WTable()),
	_label(new Wt::WText("Label")),
	_invalidMessage(new Wt::WText("Invalid")),
	_listHeader(new Wt::WText("Header", _list->elementAt(0 ,0))){

	_invalidMessage->hide();

	_setTemplate();
	_setStyle();

	bindWidget("label", _label);
	bindWidget("info", _invalidMessage);

	Wt::WContainerWidget* field = new Wt::WContainerWidget();
	field->setWidth(Wt::WLength("100%"));
	field->addWidget(_itensCombo);
	field->addWidget(_addItem);
	field->addWidget(new Wt::WBreak());
	field->addWidget(_list);
	bindWidget("field", field);
}

template <class T>
void ListField<T>::_setStyle(){
	_itensCombo->addStyleClass("form-control");
	_itensCombo->setAttributeValue("style", "display:inline;");
	_itensCombo->setWidth(Wt::WLength("70	%"));
	_itensCombo->setMargin(Wt::WLength("10%"), Wt::Right);
	_addItem->setStyleClass("btn btn-info");
	_list->setLineHeight(Wt::WLength(30));

	_list->setMargin(10, Wt::Top);
	_list->setHeaderCount(1);
	_list->elementAt(0, 0)->setContentAlignment(Wt::AlignCenter);
	_list->rowAt(0)->setStyleClass("table-info");
	_list->addStyleClass("table-bordered table-striped");
	_list->setWidth(Wt::WLength("100%"));
}

template <class T>
void ListField<T>::setHeader(std::string header){
	_listHeader->setText(header);
}

template <class T>
void ListField<T>::addItem(std::string itemName, T item){
	if(_itensCombo->currentIndex() > 0){
		_itensCombo->addItem(itemName);
		_listMap.emplace(_itensCombo->count(), item);
	}else{
		std::cout << "ListField::addItem: invalid item: index " << _itensCombo->currentIndex() << std::endl;
	}
}

template <class T>
std::vector<T> ListField<T>::getList(){
	std::vector<T> list;
	auto copyToVector = [&list](std::pair<int, T> par){
		return false;
	};

	std::copy_if(std::begin(_listMap), std::end(_listMap), copyToVector);
}

template <class T>
void ListField<T>::_setTemplate(){
	setTemplateText(Wt::WString::tr("field"));
}

template <class T>
void ListField<T>::_updateInvalidMessage(std::string message){
	_invalidMessage->setText(message);
}

template <class T>
void ListField<T>::_updateLabel(std::string label){
	_label->setText(label);
}

} /* namespace SiconfFields */

#endif /* VIEW_FIELDS_LISTFIELD_H_ */
