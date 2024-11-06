#ifndef IMAGETOOL_H
#define IMAGETOOL_H

#include <QImage>
#include <qcolor.h>

class ImageTool
{
public:
    ImageTool();
    void static flipImage(QImage& image, bool isVerticalFlip);
    void static rotateImage(QImage& image);
    void static fillBlankWithColor(QImage& image, QColor color);
};

#endif // IMAGETOOL_H
