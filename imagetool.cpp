#include "imagetool.h"
#include "qpainter.h"
#include <QDebug>

ImageTool::ImageTool() {}

void ImageTool::flipImage(QImage &image, bool isVerticalFlip)
{
    // checking image is existed or not.
    if(image.isNull())
    {
        return;
    }

    //using boolean isVerticalFlip to check whether we try to flip vertical
    //or horizontal by using mirrored function.
    if (isVerticalFlip)
    {
        image = image.mirrored(false, true);
    }
    else
    {
        image = image.mirrored(true, false);
    }

}


void ImageTool::rotateImage(QImage &image)
{
    if(image.isNull())
    {
        return;
    }

    // Using QTransform to rotate 90 degrees clockwise
    QTransform rotateImage;
    rotateImage.rotate(90);
    image = image.transformed(rotateImage);

}


void ImageTool::fillBlankWithColor(QImage &image, const QColor& color)
{
    if(image.isNull())
    {
        return;
    }

    // go over each pixel and change the color by using setpixelcolor.
    for(int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            QColor pixel = image.pixelColor(x, y);
            if(pixel.alpha() == 0)
            {
                image.setPixelColor(x, y, color);
            }
        }
    }

}

void ImageTool::loadImage(QImage &image, const QString& imagePath){
    QImage loadedImage(imagePath);

    if(!loadedImage.isNull())
    {
        loadedImage = loadedImage.scaled(image.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPainter painter(&image);
        painter.drawImage(0, 0, loadedImage);
        painter.end();
    }
    else
    {
        qWarning() << " Failed to load image from the given path !! " << imagePath;
    }
}

void ImageTool::exportImage(const QImage& image, const QString& imagePath){
    image.save(imagePath, "PNG");
}
