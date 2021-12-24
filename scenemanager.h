#pragma once

#include <QObject>
#include "files.h"
class QGraphicsScene;
class SceneManager : public QObject
{
    Q_OBJECT
public:
    explicit SceneManager(QObject *parent = nullptr);

    QGraphicsScene* scene();
    QStringList supportedExtensions();
    void openImage(const QString& fullpath);

    void nextImage();
    void previousImage();
    bool hasNext();
    bool hasPrevious();

    void fitInView();
    bool isFileSupported(const QString& fullpath);

signals:
    void imageChanged(const QString& fileName);
private:
    void showImage(const QString& fullpath);
private:
    Files files;
    QGraphicsScene* imageScene = nullptr;
    const QStringList imgExtensions = {"*.png","*.bmp","*.jpg","*.jpeg"};

};

