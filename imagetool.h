#ifndef IMAGETOOL_H
#define IMAGETOOL_H

#include <QImage>
#include <qcolor.h>

class ImageTool
{
public:
    ///
    /// \brief ImageTool: default constructor
    ///
    ImageTool();

    ///
    /// \brief flipImage: flip the image vertical or horzontal
    /// \param image: The QImage to be flipped
    /// \param isVerticalFlip: check whether is vertical or horizontal.
    ///
    void static flipImage(QImage& image, bool isVerticalFlip);

    ///
    /// \brief rotateImage: rotate the image 90 degrees once
    /// \param image: The image that be rotated
    ///
    void static rotateImage(QImage& image);

    ///
    /// \brief fillBlankWithColor: fill the blank color for the image
    /// \param image: The image that being filled color
    /// \param color: the color that we want to fill
    ///
    void static fillBlankWithColor(QImage& image, QColor color);
};

#endif // IMAGETOOL_H
