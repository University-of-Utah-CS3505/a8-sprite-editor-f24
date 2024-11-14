#ifndef IMAGETOOL_H
#define IMAGETOOL_H

#include <QImage>
#include <qcolor.h>

/**
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of canvasLabel.h : TO BE UPDATED
 *
 *  Date Modified : November 10, 2024
 *
 *  Header class for ImageTool.h

*/

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
    void static flipImage(QImage &image, bool isVerticalFlip);

    ///
    /// \brief rotateImage: rotate the image 90 degrees once
    /// \param image: The image that be rotated
    ///
    void static rotateImage(QImage &image);

    ///
    /// \brief fillBlankWithColor: fill the blank color for the image
    /// \param image: The image that being filled color
    /// \param color: the color that we want to fill
    ///
    void static fillBlankWithColor(QImage &image, const QColor &color);

    void static loadImage(QImage &image, const QString &imagePath);

    void static exportImage(const QImage &image, const QString &imagePath);
};

#endif // IMAGETOOL_H
