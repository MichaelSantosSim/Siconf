/*
 * PDFResource.h
 *
 *  Created on: Oct 25, 2015
 *      Author: michael
 */

#ifndef SRC_UTILS_PDFRESOURCE_H_
#define SRC_UTILS_PDFRESOURCE_H_

#include <Wt/WPainter>
#include <Wt/WPdfImage>
#include <Wt/WPushButton>
#include <Wt/WResource>
#include <Wt/WObject>

namespace SiconfUtils {

class SamplePdfResource : public Wt::WPdfImage{
public:
    SamplePdfResource(Wt::WObject *parent = 0)
        : Wt::WPdfImage(400, 300, parent)
    {
        suggestFileName("line.pdf");
        paint();
    }

private:
    void paint() {
        Wt::WPainter painter(this);

        Wt::WPen thickPen;
        thickPen.setWidth(5);
        painter.setPen(thickPen);
        painter.drawLine(50, 250, 150, 50);
        painter.drawLine(150, 50, 250, 50);

        painter.drawText(0, 0, 400, 300, Wt::AlignCenter | Wt::AlignTop, "Hello, PDF");
    }
};

} /* namespace SiconfUtils */

#endif /* SRC_UTILS_PDFRESOURCE_H_ */
