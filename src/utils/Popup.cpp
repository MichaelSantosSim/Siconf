/*
 * Popup.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: michael
 */

#include "Popup.h"

namespace SiconfUtils {

Popup::Popup(const std::string& message, const std::string& header) : Wt::WMessageBox() {
	setWidth(250);
	titleBar()->setContentAlignment(Wt::AlignCenter);
	setCaption(Wt::WString(header));
	contents()->setContentAlignment(Wt::AlignCenter);
	new Wt::WText(message, contents());

	Wt::WPushButton* ok = new Wt::WPushButton("ok", footer());
	ok->setStyleClass("btn btn-primary");
	ok->clicked().connect(std::bind([=](){
		delete this;
	}));

	show();
	ok->setFocus();
}

Popup::Popup(Wt::WContainerWidget* container, const std::string& header) : Wt::WMessageBox() {

	titleBar()->setContentAlignment(Wt::AlignCenter);
	setCaption(Wt::WString(header));
	contents()->setContentAlignment(Wt::AlignCenter);
	contents()->addWidget(container);

	Wt::WPushButton* ok = new Wt::WPushButton("ok", footer());
	ok->setStyleClass("btn btn-primary");
	ok->clicked().connect(std::bind([=](){
		delete this;
	}));

	show();
	ok->setFocus();
}

} /* namespace SiconfUtils */
