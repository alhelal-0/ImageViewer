#include "mainwindow.h"
#include "scenemanager.h"
#include <ivapplication.h>

int main(int argc, char *argv[])
{
    IvApplication a(argc, argv);

    QString path;
    auto arguments = a.arguments();

    SceneManager sceneManager;
    MainWindow w{sceneManager};
    w.show();
#ifdef Q_OS_MACOS
    QObject::connect(&a,&IvApplication::openFile,
                     &w,&MainWindow::openImage);

#else
    if(arguments.size()>1){
        path = arguments[1];
        w.openImage(path);
    }

#endif
    return a.exec();
}
