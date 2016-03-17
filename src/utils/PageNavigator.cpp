/*
 * PageNavigator.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: michael
 */

#include "PageNavigator.h"

namespace SiconfUtils {

PageNavigator::PageNavigator(Wt::WContainerWidget* parent) : _mainStack(new Wt::WStackedWidget(parent)) {
	Wt::WApplication* app = Wt::WApplication::instance();
	app->internalPathChanged().connect(this, &PageNavigator::setInternalPath);
	_mainStack->setStyleClass("main");
}

void PageNavigator::setInternalPath(const std::string& path){

	try{
		Wt::WApplication::instance()->setInternalPath(path);
		_mainStack->setCurrentWidget(_pageMap.at(path));
	}catch(std::out_of_range& e){
		std::cout << "setInternalPath: " << e.what() << std::endl;
		std::cout << "setInternalPath: " << path << " is invalid. Setting first page for default" << std::endl;
		_mainStack->setCurrentIndex(0);
	}
}

void PageNavigator::addPage(SiconfPage::AbstractPage* page){
	std::cout << page->path() << " added to navigation" << std::endl;
	_pageMap.emplace(page->path(), page);
	_mainStack->addWidget(page);
}

} /* namespace SiconfUtils */
