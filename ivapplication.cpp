#include "ivapplication.h"

#ifdef Q_OS_MACOS
#include <QFileOpenEvent>
#endif
IvApplication::IvApplication(int argc, char** argv)
    :QApplication(argc,argv)
{

}

#ifdef Q_OS_MACOS
bool IvApplication::event(QEvent *event)
{
    if(event->type()==QEvent::FileOpen)
    {
        QFileOpenEvent* openEvent = static_cast<QFileOpenEvent*>(event);
        emit openFile(openEvent->file());
    }
    return QApplication::event(event);
}

#endif
