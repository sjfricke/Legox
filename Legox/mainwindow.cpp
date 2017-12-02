#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mp_ui(new Ui::MainWindow)
{
    mp_ui->setupUi(this);

    createMenu();
    setupStatusBar();

//    connect(mp_ui->myGLWidget, SIGNAL(xRotationChanged(int)), mp_ui->rotXSlider_2, SLOT(setValue(int)));
//    connect(mp_ui->myGLWidget, SIGNAL(yRotationChanged(int)), mp_ui->rotYSlider_2, SLOT(setValue(int)));
//    connect(mp_ui->myGLWidget, SIGNAL(zRotationChanged(int)), mp_ui->rotZSlider_2, SLOT(setValue(int)));
//    connect(mp_ui->rotXSlider_2, SIGNAL(valueChanged(int)), mp_ui->myGLWidget, SLOT(setXRotation(int)));
//    connect(mp_ui->rotYSlider_2, SIGNAL(valueChanged(int)), mp_ui->myGLWidget, SLOT(setYRotation(int)));
//    connect(mp_ui->rotZSlider_2, SIGNAL(valueChanged(int)), mp_ui->myGLWidget, SLOT(setZRotation(int)));

}

MainWindow::~MainWindow()
{
    delete mp_ui;
}

void MainWindow::createMenu()
{
    mp_fileMenu = mp_ui->menuBar->addMenu(tr("&File"));
    mp_editMenu = mp_ui->menuBar->addMenu(tr("E&dit"));
    mp_viewMenu = mp_ui->menuBar->addMenu(tr("V&iew"));
    mp_helpMenu = mp_ui->menuBar->addMenu(tr("H&elp"));
    mp_newAction = mp_fileMenu->addAction(tr("New"));
    mp_openAction = mp_fileMenu->addAction(tr("Open"));
    mp_saveAction = mp_fileMenu->addAction(tr("Save"));
    mp_saveAsAction = mp_fileMenu->addAction(tr("Save As"));
    mp_exitAction = mp_fileMenu->addAction(tr("E&xit"));
    mp_undoAction = mp_editMenu->addAction(tr("Edit"));
    mp_zoomAction = mp_viewMenu->addAction(tr("Zoom"));
    mp_aboutAction = mp_helpMenu->addAction(tr("Info"));

    connect(mp_openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(mp_exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::openFile()
{
    m_qFilePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("STL Files (*.obj)"));
    if (!m_qFilePath.isNull()) {

        if (0 != m_legox.newFile(m_qFilePath)) {
            // TODO handle error
        }


    }
}

void MainWindow::setupStatusBar()
{
    mp_ui->statusBar->addWidget(new QLabel("Lego Counut:\t\t", NULL));
    mp_ui->statusBar->addWidget(new QLabel("Volume:\t\t", NULL));
    mp_ui->statusBar->addWidget(new QLabel("Mass:\t\t", NULL));
}
