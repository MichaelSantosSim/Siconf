/*
 * PageNavigator.h
 *
 *  Created on: Aug 23, 2015
 *      Author: michael
 */

#ifndef UTILS_PAGENAVIGATOR_H_
#define UTILS_PAGENAVIGATOR_H_

#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WApplication>
#include "../view/pages/AbstractPage.h"

namespace SiconfUtils {

class PageNavigator {
public:
	PageNavigator(Wt::WContainerWidget* parent);
	void addPage(SiconfPage::AbstractPage* page);
	void setInternalPath(const std::string& path);
	void updatePages();
private:
	std::map<std::string, SiconfPage::AbstractPage*> _pageMap;
	Wt::WStackedWidget*_mainStack;

};

} /* namespace SiconfUtils */

#endif /* UTILS_PAGENAVIGATOR_H_ */
