#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{}


void Model::receiveMouseEvent(MouseButton button){

}

void Model::receiveCurrentFrameIndex(int frameIndex){

}

void Model::addNewFrameAtCurrentFrame(){

}

void Model::removeCurrentFrame(){

}

void Model::cloneCurrentFrame(){

}

void Model::receiveFPS(int fps){

}

void Model::updateBrushType(Brush brush){

}

//Image tool
void Model::rotateImage(){}
void Model::flipImageAlongY(){}
void Model::flipImageAlongX(){}
void Model::loadImage(QString imagePath){}
void Model::fillBlankArea(){}
void Model::clearCanvas(){}
//Saving
void Model::openFile(QString fileName){}
void Model::saveFile(QString fileName){}
