#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SceneManager;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(SceneManager& manager, QWidget *parent = nullptr);
    ~MainWindow();
    void openImage(const QString& fullpath);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent  *event) override;
    void dropEvent(QDropEvent *event) override;
private:
    void onNextBtnClicked();
    void onPreviousBtnClicked();

    void onImageChanged(const QString& fileName);

    void previousImage();
    void nextImage();
    void fitInView();
    void zoomIn();
    void zoomOut();

    void showOpenDialog();
    void updateButtons();

private:
    Ui::MainWindow *ui;
    SceneManager& sceneManager;
    const QString defaultWindowTitle = "ImageViewer for Topaz Labs";

};

