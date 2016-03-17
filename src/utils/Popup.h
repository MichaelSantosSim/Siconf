/*
 * Popup.h
 *
 *  Created on: Sep 17, 2015
 *      Author: michael
 */

#ifndef SRC_UTILS_POPUP_H_
#define SRC_UTILS_POPUP_H_

#include <Wt/WMessageBox>
#include <Wt/WPushButton>
#include <Wt/WText>

namespace SiconfUtils {

class Popup: public Wt::WMessageBox {
public:
	Popup(const std::string& message, const std::string& header);
	Popup(Wt::WContainerWidget* container, const std::string& header);
};

} /* namespace SiconfUtils */

#endif /* SRC_UTILS_POPUP_H_ */
