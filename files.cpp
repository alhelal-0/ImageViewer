#include "files.h"
#include <QString>
#include <QFileInfo>
#include <QDir>

Files::Files()
{

}

void Files::setExtensions(const QStringList& extensions){
    supportedExtensions = extensions;
}
void Files::openFile(const QString& fullPath){
    QFileInfo current(fullPath);
    QDir dir = current.absoluteDir();
    currentFilePath = fullPath;
    currentFileName = current.fileName();
    fileNamesInCurrentPath = dir.entryList(supportedExtensions, QDir::Files,QDir::Name);

    int index = fileNamesInCurrentPath.indexOf(currentFileName);

    hasPrevious = index !=0? true : false;
    hasNext = index != fileNamesInCurrentPath.size()-1?true:false;

}

QString Files::nextFile(){
    QFileInfo current(currentFilePath);
    QDir dir = current.absoluteDir();

    int index = fileNamesInCurrentPath.indexOf(currentFileName);
    if(index < fileNamesInCurrentPath.size()-1){
        hasPrevious = true;
        if(index == fileNamesInCurrentPath.size()-2){
            hasNext = false;
        }
        currentFilePath = dir.absoluteFilePath(fileNamesInCurrentPath.at(index+1));
        current = QFileInfo(currentFilePath);
        currentFileName = current.fileName();
    }
    return currentFilePath;
}

QString Files::previousFile(){
    QFileInfo current(currentFilePath);
    QDir dir = current.absoluteDir();

    int index = fileNamesInCurrentPath.indexOf(currentFileName);
    if(index > 0){
        hasNext = true;
        if(index == 1){
            hasPrevious = false;
        }
        currentFilePath = dir.absoluteFilePath(fileNamesInCurrentPath.at(index-1));
        current = QFileInfo(currentFilePath);
        currentFileName = current.fileName();
    }
    return currentFilePath;
}

bool Files::hasNextFile(){
    return hasNext;
}
bool Files::hasPreviousFile(){
    return hasPrevious;
}

QString Files::getCurrentFilename(){
    return currentFileName;
}
