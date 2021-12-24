#include "scenemanager.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImageReader>
SceneManager::SceneManager(QObject *parent) : QObject{parent}
{
    imageScene = new QGraphicsScene(this);
    files.setExtensions(imgExtensions);
}
QGraphicsScene *SceneManager::scene()
{
    return imageScene;
}

QStringList SceneManager::supportedExtensions()
{
    return imgExtensions;
}

void SceneManager::openImage(const QString &fullpath)
{
    files.openFile(fullpath);
    showImage(fullpath);
}

void SceneManager::nextImage()
{
    showImage(files.nextFile());
}

void SceneManager::previousImage()
{
    showImage(files.previousFile());
}

bool SceneManager::hasNext()
{
    return files.hasNextFile();
}

bool SceneManager::hasPrevious()
{
    return files.hasPreviousFile();
}

void SceneManager::fitInView()
{
    if(imageScene->items().size() && imageScene->views().size()){
        auto view = imageScene->views().at(0);
        view->fitInView(imageScene->items().at(0), Qt::KeepAspectRatio);
        view->setSceneRect(imageScene->items().at(0)->boundingRect());
    }
}

bool SceneManager::isFileSupported(const QString &fullpath)
{
    for(auto ext :imgExtensions ){
        ext = ext.remove(0,1);
        if(fullpath.endsWith(ext, Qt::CaseInsensitive)){
            return true;
        }
    }
    return false;
}

void SceneManager::showImage(const QString &fullpath)
{
    imageScene->clear();

    QImageReader imgReader(fullpath);
    imgReader.setAutoTransform(true);

    QImage img = imgReader.read();

    if(!img.isNull()){
        QPixmap pixmap = QPixmap::fromImage(img);

        imageScene->addPixmap(pixmap);
        imageScene->update();

        emit imageChanged(files.getCurrentFilename());
    }
}

