/*
 * Anchor.h
 *
 *  Created on: Oct 1, 2015
 *      Author: michael
 */

#ifndef SRC_VIEW_WIDGETS_ANCHOR_H_
#define SRC_VIEW_WIDGETS_ANCHOR_H_

#include <Wt/WAnchor>

namespace SiconfWidget {
template <class T>
class Anchor: public Wt::WAnchor {
public:
	Anchor(T object, Wt::WContainerWidget* parent = nullptr) : Wt::WAnchor(parent), _object(object){addStyleClass("Wt-Anchor");};
	Anchor(T object, std::string name, Wt::WContainerWidget* parent = nullptr) : Wt::WAnchor(parent), _object(object){setText(name); addStyleClass("Wt-Anchor");};
	T get(){return _object;};
private:
	T _object;
};
} /* namespace SiconfWidget */

#endif /* SRC_VIEW_WIDGETS_ANCHOR_H_ */
