#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenemanager.h"

#include <QFileDialog>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDropEvent>
#include <QMimeData>

MainWindow::MainWindow(SceneManager& manager,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    ,sceneManager(manager)
{
    ui->setupUi(this);

    setWindowTitle(defaultWindowTitle);
    ui->imageView->setScene(sceneManager.scene());

    connect(ui->nextBtn, &QPushButton::clicked,
            this, &MainWindow::onNextBtnClicked);
    connect(ui->prevBtn,&QPushButton::clicked,
            this, &MainWindow::onPreviousBtnClicked);
    connect(&sceneManager,&SceneManager::imageChanged,
            this, &MainWindow::onImageChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(const QString &fullpath)
{
    if(sceneManager.isFileSupported(fullpath)){
        sceneManager.openImage(fullpath);
        fitInView();
    }
    updateButtons();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            previousImage();
            break;
        case Qt::Key_Right:
            nextImage();
            break;
         case Qt:: Key_O:
            if(event->modifiers() & Qt::ControlModifier)
                showOpenDialog();
            break;
         default:
            QWidget::keyPressEvent(event);
    }

}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()>0)
        zoomIn();
    else
        zoomOut();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        fitInView();
    QWidget::mouseDoubleClickEvent(event);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    auto mimeData = event->mimeData();
    if(mimeData->hasUrls()){
        auto urls = mimeData->urls();
        if(sceneManager.isFileSupported(urls[0].toLocalFile())){
            event->acceptProposedAction();
        }
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    auto urls = event->mimeData()->urls();
    if(urls.size()){
        openImage(urls[0].toLocalFile());
    }
}

void MainWindow::onNextBtnClicked()
{
    nextImage();
}

void MainWindow::onPreviousBtnClicked()
{
    previousImage();
}

void MainWindow::onImageChanged(const QString &fileName)
{
    setWindowTitle(QString("%0 - \"%1\"").arg(defaultWindowTitle).arg(fileName));
}

void MainWindow::previousImage()
{
    if(sceneManager.hasPrevious()){
        sceneManager.previousImage();
        fitInView();
    }
    updateButtons();

}

void MainWindow::nextImage()
{
    if(sceneManager.hasNext()){
        sceneManager.nextImage();
        fitInView();
    }
    updateButtons();
}

void MainWindow::fitInView()
{
    sceneManager.fitInView();
}

void MainWindow::zoomIn()
{
    ui->imageView->scale(1.1,1.1);
}

void MainWindow::zoomOut()
{
    ui->imageView->scale(0.9,0.9);
}

void MainWindow::showOpenDialog()
{
    QString imageExtensions = QString("Images (%0)").arg(sceneManager.supportedExtensions().join(" "));
    QString path = QFileDialog::getOpenFileName(this, "Open image","", imageExtensions);
    if(path.size())
        openImage(path);
}

void MainWindow::updateButtons()
{
    ui->prevBtn->setEnabled(sceneManager.hasPrevious());
    ui->nextBtn->setEnabled(sceneManager.hasNext());
}





