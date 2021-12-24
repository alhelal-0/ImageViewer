#pragma once
#include <QApplication>

class IvApplication : public QApplication
{
    Q_OBJECT
public:
    IvApplication(int argc, char** argv);
#ifdef Q_OS_MACOS
signals:
    void openFile(const QString& filePath);
protected:
    bool event(QEvent* event) override;
#endif
};

