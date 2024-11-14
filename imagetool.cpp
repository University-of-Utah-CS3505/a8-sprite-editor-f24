#include "imagetool.h"
#include "qpainter.h"
#include <QDebug>

/**
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of canvasLabel.h : TO BE UPDATED
 *
 *  Date Modified : November 10, 2024

 *  ImageTool contains methods like flipImage, rotateImage, fillBlankWithColor, loadImage and exportImage
 *  providing the users with all the functions required for mainpulating the image
 *
 */

/// Default constructor
ImageTool::ImageTool() {}

/**
 * @brief ImageTool::flipImage
 * @param image Reference to the image which is the canvas to be flipped
 * @param isVerticalFlip flag to determine if image has to be flipped vertically or horizontally
 */
void ImageTool::flipImage(QImage &image, bool isVerticalFlip)
{
    // checking image is existed or not.
    if (image.isNull())
    {
        return;
    }

    // using boolean isVerticalFlip to check whether we try to flip vertical
    // or horizontal by using mirrored function.
    if (isVerticalFlip)
    {
        image = image.mirrored(false, true);
    }
    else
    {
        image = image.mirrored(true, false);
    }
}

/**
 * @brief ImageTool::rotateImage
 * @param image Reference to image that has to be rotated
 */
void ImageTool::rotateImage(QImage &image)
{
    if (image.isNull())
    {
        return;
    }

    // Using QTransform to rotate 90 degrees clockwise
    QTransform rotateImage;
    rotateImage.rotate(90);
    image = image.transformed(rotateImage);
}

/**
 * @brief ImageTool::fillBlankWithColor
 * @param image Reference to image that has to be colored up
 * @param color the color with the canvas/image object has to be filled up with
 */
void ImageTool::fillBlankWithColor(QImage &image, const QColor &color)
{
    if (image.isNull())
    {
        return;
    }

    // go over each pixel and change the color by using setpixelcolor.
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            QColor pixel = image.pixelColor(x, y);
            if (pixel.alpha() == 0)
            {
                image.setPixelColor(x, y, color);
            }
        }
    }
}

/**
 * @brief ImageTool::loadImage
 * @param image Reference to image that has to be loaded
 * @param imagePath the path from which image has to be loaded
 */
void ImageTool::loadImage(QImage &image, const QString &imagePath)
{
    QImage loadedImage(imagePath);

    if (!loadedImage.isNull())
    {
        loadedImage = loadedImage.scaled(image.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPainter painter(&image);
        // draws the image from point 0, 0
        painter.drawImage(0, 0, loadedImage);
        painter.end();
    }
    else
    {
        qWarning() << " Failed to load image from the given path !! " << imagePath;
    }
}

/**
 * @brief ImageTool::exportImage
 * @param image Reference to image that has to be exported
 * @param imagePath the path to which image has to be exported
 */
void ImageTool::exportImage(const QImage &image, const QString &imagePath)
{
    image.save(imagePath, "PNG");
}
