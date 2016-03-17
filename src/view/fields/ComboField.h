/*
 * ComboField.h
 *
 *  Created on: Jul 9, 2015
 *      Author: michael
 */

#ifndef VIEW_FORMS_COMBOFIELD_H_
#define VIEW_FORMS_COMBOFIELD_H_

#include "AbstractField.h"
#include <Wt/WComboBox>
#include <Wt/WText>
#include <map>

	/*
	 *  Nota:
	 *  A implementacao de classes com templates deve ser feita no mesmo arquivo
	 *  do cabeçalho, devido á alguns problemas de localizacao do tipo tratado
	 *
	 */


namespace SiconfFields {
template <class T>
class ComboField: public AbstractField {
public:
	ComboField();
	void addItem(std::string itemName, T object);
	bool validate();
	void reset();
	T getInput();
	inline Wt::WComboBox* comboBox(){return _fieldInput;}

private:

	void _setTemplate();
	void _updateInvalidMessage(std::string message);
	void _updateLabel(std::string label);

	Wt::WText* 		_fieldLabel;
	Wt::WText* 		_fieldInvalidMessage;
	Wt::WComboBox*	_fieldInput;

	std::map<std::string, T> _itens;
};


// Implementacao
template <class T>
ComboField<T>::ComboField() : AbstractField(),
							_fieldLabel(new Wt::WText("Campo")),
							_fieldInvalidMessage(new Wt::WText("Selecione um item")),
							_fieldInput(new Wt::WComboBox()){

	_fieldInput->addItem("Selecione");

	_fieldInvalidMessage->hide();

	_fieldInput->setStyleClass("form-control");
	_setTemplate();

	bindWidget("label", _fieldLabel);
	bindWidget("field", _fieldInput);
	bindWidget("info", _fieldInvalidMessage);
}

template <class T>
void ComboField<T>::reset(){
	_fieldInput->clear();
	_fieldInput->addItem("Selecione");
	_itens.clear();
}

template <class T>
T ComboField<T>::getInput(){
	return _itens.at(_fieldInput->currentText().toUTF8());
}

template <class T>
void ComboField<T>::addItem(std::string itemName, T object){
	_fieldInput->addItem(itemName);
	_itens.emplace(itemName, object);
}

template <class T>
bool ComboField<T>::validate(){

	if(_itens.count(_fieldInput->currentText().toUTF8()) > 0){
		_fieldInvalidMessage->hide();
		return true;
	}
	_fieldInvalidMessage->show();
	return false;
}

template <class T>
void ComboField<T>::_setTemplate(){
	setTemplateText(Wt::WString::tr("field"));
}

template <class T>
void ComboField<T>::_updateInvalidMessage(std::string message){
	_fieldInvalidMessage->setText(message);
}

template <class T>
void ComboField<T>::_updateLabel(std::string label){
	_fieldLabel->setText(label);
}

} /* namespace SiconfFields */

#endif /* VIEW_FORMS_COMBOFIELD_H_ */
