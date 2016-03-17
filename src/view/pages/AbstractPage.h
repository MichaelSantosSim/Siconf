/*
 * AbstractPage.h
 *
 *  Created on: Aug 23, 2015
 *      Author: michael
 */

#ifndef VIEW_PAGES_ABSTRACTPAGE_H_
#define VIEW_PAGES_ABSTRACTPAGE_H_

#include <Wt/WContainerWidget>

namespace SiconfPage {

class AbstractPage: public Wt::WContainerWidget {
public:
	AbstractPage(std::string path);
	inline std::string path(){return _path;}

private:

	std::string _path;
};

} /* namespace SiconfPage */

#endif /* VIEW_PAGES_ABSTRACTPAGE_H_ */
